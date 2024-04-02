#include "uav_node.h"
#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/TwistStamped.h>
#include <geometry_msgs/Vector3Stamped.h>
#include <sensor_msgs/NavSatFix.h>
#include <sensor_msgs/Imu.h>
#include <tf/transform_datatypes.h>
#include <mavros_msgs/PositionTarget.h>
#include <mavros_msgs/AttitudeTarget.h>

#include <matrix/math.hpp>
using matrix::Eulerf;
using matrix::Quatf;

UavNode::fms_fusion UavNode::fusion{};

UavNode::UavNode(int uav_id) :
    ros::NodeHandle(),
    _uav_id(uav_id),
    _node_name("uav" + std::to_string(uav_id))
{
}

int UavNode::initialize()
{
    _set_mode.request.custom_mode = "OFFBOARD";
    _arm_cmd.request.value = true;

    state_sub = subscribe<mavros_msgs::State>(_node_name + "/mavros/state", 10, [this](const mavros_msgs::State::ConstPtr& msg){
        if (_state.connected != msg->connected || _state.armed != msg->armed || _state.mode != msg->mode)
        {
            ROS_INFO("%s connected: %d, armed: %d, mode: %s", _node_name.c_str(), msg->connected, msg->armed, msg->mode.c_str());
        }
        _state = *msg;
    });

#if AIRCRAFT_TYPE == FIXED_WING
    setpoint_raw_att_pub = advertise<mavros_msgs::AttitudeTarget>(_node_name + "/mavros/setpoint_raw/attitude", 10);
#else
    setpoint_raw_local_pub = advertise<mavros_msgs::PositionTarget>(_node_name + "/mavros/setpoint_raw/local", 10);
#endif

    arming_client = serviceClient<mavros_msgs::CommandBool>(_node_name + "/mavros/cmd/arming");
    set_mode_client = serviceClient<mavros_msgs::SetMode>(_node_name + "/mavros/set_mode");

    // FMS INPUT subscriber
    local_pose_sub = subscribe<geometry_msgs::PoseStamped>(_node_name + "/mavros/local_position/pose", 10, [this](const geometry_msgs::PoseStamped::ConstPtr& msg){
        //ENU to NED
        _fms_in.INS_Out.x_R = msg->pose.position.y;
        _fms_in.INS_Out.y_R = msg->pose.position.x;
        _fms_in.INS_Out.h_R = msg->pose.position.z;
        tf::Quaternion quat_enu;
        tf::quaternionMsgToTF(msg->pose.orientation, quat_enu);
        double roll, pitch, yaw;
        tf::Matrix3x3(quat_enu).getRPY(roll, pitch, yaw);
        _fms_in.INS_Out.phi     = roll;
        _fms_in.INS_Out.theta   = -pitch;
        _fms_in.INS_Out.psi     = M_PI_2 - yaw;
        ROS_DEBUG("UAV %s: x_R: %f, y_R: %f, h_R: %f, phi: %f, theta: %f, psi: %f", _node_name.c_str(), _fms_in.INS_Out.x_R, _fms_in.INS_Out.y_R, _fms_in.INS_Out.h_R,
                _fms_in.INS_Out.phi, _fms_in.INS_Out.theta, _fms_in.INS_Out.psi);
    });

    local_vel_sub = subscribe<geometry_msgs::TwistStamped>(_node_name + "/mavros/local_position/velocity_local", 10, [this](const geometry_msgs::TwistStamped::ConstPtr& msg){
        //ENU to NED
        _fms_in.INS_Out.vn = msg->twist.linear.y;
        _fms_in.INS_Out.ve = msg->twist.linear.x;
        _fms_in.INS_Out.vd = -msg->twist.linear.z;
        _fms_in.INS_Out.airspeed = std::sqrt(std::pow(_fms_in.INS_Out.vn, 2) + std::pow(_fms_in.INS_Out.ve, 2) + std::pow(_fms_in.INS_Out.vd, 2));
        ROS_DEBUG("UAV %s: vn: %f, ve: %f, vd: %f, airspeed: %f", _node_name.c_str(), _fms_in.INS_Out.vn, _fms_in.INS_Out.ve, _fms_in.INS_Out.vd, _fms_in.INS_Out.airspeed);
    });

    ROS_INFO("UAV node %s created", name());
    return 0;
}
void UavNode::parameter_update()
{
    FMS_PARAM.FW_AIRSPD_TRIM = 15.f;
    FMS_PARAM.FW_HEIGHT_TRIM = 50;
    FORMATION_PARAM.UAV_ID = _uav_id + 1;

    CONTROL_PARAM.FW_P_LIM_MIN = -15.f * M_DEG_TO_RAD;
    CONTROL_PARAM.FW_THR_MIN = 0.05f;
    CONTROL_PARAM.FW_THR_MAX = 0.6f;
    CONTROL_PARAM.FW_THR_TRIM = 0.25f;
    CONTROL_PARAM.FW_AIRSPD_MIN = 10.f;
    CONTROL_PARAM.FW_AIRSPD_MAX = 20.f;
    CONTROL_PARAM.FW_AIRSPD_TRIM = 15.f;
    CONTROL_PARAM.FW_AIRSPD_STALL = 7.f;
    CONTROL_PARAM.FW_ARSP_MODE = 0;
    CONTROL_PARAM.FW_ARSP_SCALE_EN = 1;
    CONTROL_PARAM.FW_T_TAS_TC = 5.f;
    CONTROL_PARAM.FW_T_CLMB_MAX = 8.f;
    CONTROL_PARAM.FW_T_SINK_MAX = 2.7f;
    CONTROL_PARAM.FW_T_SINK_MIN = 2.2f;
    CONTROL_PARAM.FW_T_CLMB_R_SP = 3.f;
    CONTROL_PARAM.FW_T_SINK_R_SP = 2.f;

    CONTROL_PARAM.FW_T_I_GAIN_THR = 0.f;
    CONTROL_PARAM.FW_T_RLL2THR = 0.f;
    CONTROL_PARAM.FW_T_I_GAIN_PIT = 0.f;
}

void UavNode::mission_decompose()
{   
    switch (_fms_out.FMS_Out.state)
    {
    case VehicleState::FormAssemble:
    {
        // if mission data is updated
        if (_fms_in.Mission_Data.timestamp != fusion.mission.timestamp)
        {
            _fms_in.Mission_Data.timestamp = fusion.mission.timestamp;
            _fms_in.Mission_Data.type = fusion.mission.type[_uav_id];
            _fms_in.Mission_Data.valid_items = fusion.mission.valid_items[_uav_id];
            for (size_t i = 0; i < 8; i++)
            {
                _fms_in.Mission_Data.x[i] = fusion.mission.x[3 * i + _uav_id];
                _fms_in.Mission_Data.y[i] = fusion.mission.y[3 * i + _uav_id];
                _fms_in.Mission_Data.z[i] = fusion.mission.z[3 * i + _uav_id];
                _fms_in.Mission_Data.heading[i] = fusion.mission.heading[3 * i + _uav_id];
                _fms_in.Mission_Data.ext1[i] = fusion.mission.ext1[3 * i + _uav_id];
                _fms_in.Mission_Data.ext2[i] = fusion.mission.ext2[3 * i + _uav_id];
            }
        }
        break;
    }
    case VehicleState::FormMission:
    {
        static bool already = false;
        if (_uav_id == 0 && !already && _fms_out.FMS_Out.state == VehicleState::FormMission)
        {
            already = true;
            _fms_in.Mission_Data.timestamp += 100;
            _fms_in.Mission_Data.type = uint32_t(3);
            _fms_in.Mission_Data.valid_items = 4;
            _fms_in.Mission_Data.x[0] = 1500.f;
            _fms_in.Mission_Data.y[0] = 1500.f;
            _fms_in.Mission_Data.z[0] = 50.f;

            _fms_in.Mission_Data.x[1] = 2000.f;
            _fms_in.Mission_Data.y[1] = 1500.f;
            _fms_in.Mission_Data.z[1] = 50.f;

            _fms_in.Mission_Data.x[2] = 2000.f;
            _fms_in.Mission_Data.y[2] = 1000.f;
            _fms_in.Mission_Data.z[2] = 50.f;

            _fms_in.Mission_Data.x[3] = 1500.f;
            _fms_in.Mission_Data.y[3] = 500.f;
            _fms_in.Mission_Data.z[3] = 50.f;
        }
        break;
    }
    default:
        break;
    }
}

void UavNode::pilot_cmd_decode()
{
    if (run_time_ms < 1 * 1000)
    {
        _fms_in.Pilot_Cmd.timestamp = 0;
        _fms_in.Pilot_Cmd.mode = uint32_t(PilotMode::None);
    }
    else
    {
        _fms_in.Pilot_Cmd.timestamp = 1;
        _fms_in.Pilot_Cmd.mode = uint32_t(PilotMode::FormAssemble);
    }
}

void UavNode::fms_step()
{
    fusion.cross.x_R[_uav_id] = _fms_in.INS_Out.x_R;
    fusion.cross.y_R[_uav_id] = _fms_in.INS_Out.y_R;
    fusion.cross.h_R[_uav_id] = _fms_in.INS_Out.h_R;
    fusion.cross.vn[_uav_id] = _fms_in.INS_Out.vn;
    fusion.cross.ve[_uav_id] = _fms_in.INS_Out.ve;
    fusion.cross.vd[_uav_id] = _fms_in.INS_Out.vd;
    
    // _fms_in.INS_Out; AUTOMATICALLY UPDATED BY SUBSCRIBERS
    _fms_in.Formation_Cross = fusion.cross;
    _fms_out = _fms.step(&_fms_in);

    fusion.cross.left_time[_uav_id] = _fms_out.Form_Single;
    if (_uav_id == 0 && _fms_out.Other_Mission_Data.timestamp)
    {
        fusion.mission = _fms_out.Other_Mission_Data;
    }
    ROS_DEBUG("UAV %s: setpoint roll: %f, pitch: %f, throttle: %f", _node_name.c_str(), _fms_out.att_cmd[0], _fms_out.att_cmd[1], _fms_out.throttle_cmd);

    auto get_state = [](VehicleState state) -> std::string
    {
        switch (state)
        {
        case VehicleState::None:
            return "None";
        case VehicleState::FormAssemble:
            return "FormAssemble";
        case VehicleState::FormDisband:
            return "FormDisband";
        case VehicleState::FormMission:
            return "FormMission";
        case VehicleState::Hold:
            return "Hold";
        default:
            return "UNKNOWN";
        }
    };
    ROS_INFO("UAV %s: state: %s, pose:[%.1f\t%.1f\t%.1f]", _node_name.c_str(), get_state(_fms_out.FMS_Out.state).c_str(), _fms_in.INS_Out.x_R, _fms_in.INS_Out.y_R, _fms_in.INS_Out.psi * M_RAD_TO_DEG);
}
/**
 * @brief Publish a trajectory setpoint
 *        For this example, it sends a trajectory setpoint to make the
 *        vehicle hover at 5 meters with a yaw angle of 180 degrees.
 */
void UavNode::publish_trajectory_setpoint()
{
#if AIRCRAFT_TYPE == FIXED_WING
    mavros_msgs::AttitudeTarget setpoint{};
    setpoint.header.stamp = ros::Time::now();
    /*
        uint8 IGNORE_ROLL_RATE = 1 # body_rate.x
        uint8 IGNORE_PITCH_RATE = 2 # body_rate.y
        uint8 IGNORE_YAW_RATE = 4 # body_rate.z
        uint8 IGNORE_THRUST = 64
        uint8 IGNORE_ATTITUDE = 128 # orientation field
    */
    setpoint.type_mask = mavros_msgs::AttitudeTarget::IGNORE_ROLL_RATE | mavros_msgs::AttitudeTarget::IGNORE_PITCH_RATE | mavros_msgs::AttitudeTarget::IGNORE_YAW_RATE;
    setpoint.thrust = _fms_out.throttle_cmd;
    tf::quaternionTFToMsg(tf::createQuaternionFromRPY(_fms_out.att_cmd[0], -_fms_out.att_cmd[1], 0), setpoint.orientation);
    setpoint_raw_att_pub.publish(setpoint);
#else
    mavros_msgs::PositionTarget setpoint{};
    setpoint.header.stamp = ros::Time::now();
    /*
        uint8 FRAME_LOCAL_NED = 1
        uint8 FRAME_LOCAL_OFFSET_NED = 7 //don't support
        uint8 FRAME_BODY_NED = 8
        uint8 FRAME_BODY_OFFSET_NED = 9 //don't support
    */
    setpoint.coordinate_frame = mavros_msgs::PositionTarget::FRAME_LOCAL_NED;
    /*
        uint16 IGNORE_PX = 1 # Position ignore flags
        uint16 IGNORE_PY = 2
        uint16 IGNORE_PZ = 4
        uint16 IGNORE_VX = 8 # Velocity vector ignore flags
        uint16 IGNORE_VY = 16
        uint16 IGNORE_VZ = 32
        uint16 IGNORE_AFX = 64 # Acceleration/Force vector ignore flags
        uint16 IGNORE_AFY = 128
        uint16 IGNORE_AFZ = 256
        uint16 FORCE = 512 # Force in af vector flag
        uint16 IGNORE_YAW = 1024
        uint16 IGNORE_YAW_RATE = 2048
    */  //only control vn, ve, vh, an, ae, ah(0)
    setpoint.type_mask = mavros_msgs::PositionTarget::IGNORE_PX | mavros_msgs::PositionTarget::IGNORE_PY | mavros_msgs::PositionTarget::IGNORE_PZ | 
            mavros_msgs::PositionTarget::IGNORE_YAW | mavros_msgs::PositionTarget::IGNORE_YAW_RATE;
    //NED to ENU
    // _fms_out.FMS_Out.ax_cmd;
    setpoint.velocity.y = 10;    //vn
    setpoint.velocity.x = 5;    //ve
    setpoint.velocity.z = 10;    //vh _fms_out.FMS_Out.vh_cmd;
    setpoint.acceleration_or_force.y = 0;    //an
    setpoint.acceleration_or_force.x = 10;    //ae
    setpoint.acceleration_or_force.z = 0;    //ah
    setpoint_raw_local_pub.publish(setpoint);
#endif
}

/**
 * @brief Publish the offboard control mode.
 *        For this example, only position and altitude controls are active.
 */
void UavNode::publish_offboard_control_mode()
{
    ros::Time now = ros::Time::now();
    static ros::Time last_request = now;
    if(_state.mode != "OFFBOARD" && (now - last_request > ros::Duration(5.0)))
    {
        if(set_mode_client.call(_set_mode) && _set_mode.response.mode_sent)
        {
            ROS_INFO("Offboard enabled %s", _node_name.c_str());
        }
        last_request = now;
    } else 
    {
        if(!_state.armed && (now - last_request > ros::Duration(5.0)))
        {
            if(arming_client.call(_arm_cmd) && _arm_cmd.response.success)
            {
                ROS_INFO("Vehicle armed %s", _node_name.c_str());
            }
            last_request = now;
        }
    }
}

int UavNode::spin()
{
    ros::Rate rate(CONTROL_PERIOD_HZ);

    while (ros::ok())
    {
        if (connected())
        {
            parameter_update();
            mission_decompose();
            pilot_cmd_decode();
            fms_step();
            publish_offboard_control_mode();
            publish_trajectory_setpoint();
            run_time_ms += CONTROL_PERIOD_HZ;
        }
        rate.sleep();
    }

    return 0;
}

bool UavNode::connected() const
{
    return _state.connected && _state.armed;
}

const char* UavNode::name()
{
    return _node_name.c_str();
}