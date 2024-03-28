#include "uav_node.h"
#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/TwistStamped.h>
#include <geometry_msgs/Vector3Stamped.h>
#include <sensor_msgs/NavSatFix.h>
#include <sensor_msgs/Imu.h>
#include <tf/transform_datatypes.h>
#include <mavros_msgs/PositionTarget.h>

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

    setpoint_raw_local_pub = advertise<mavros_msgs::PositionTarget>(_node_name + "/mavros/setpoint_raw/local", 10);

    arming_client = serviceClient<mavros_msgs::CommandBool>(_node_name + "/mavros/cmd/arming");
    set_mode_client = serviceClient<mavros_msgs::SetMode>(_node_name + "/mavros/set_mode");

    // FMS INPUT subscriber
    local_pose_sub = subscribe<geometry_msgs::PoseStamped>(_node_name + "/mavros/local_position/pose", 10, [this](const geometry_msgs::PoseStamped::ConstPtr& msg){
        //ENU to NED
        _fms_in.INS_Out.x_R = msg->pose.position.y;
        _fms_in.INS_Out.y_R = msg->pose.position.x;
        _fms_in.INS_Out.h_R = msg->pose.position.z;
        _fms_in.INS_Out.quat[0] = msg->pose.orientation.w;
        _fms_in.INS_Out.quat[1] = msg->pose.orientation.x;
        _fms_in.INS_Out.quat[2] = msg->pose.orientation.y;
        _fms_in.INS_Out.quat[3] = msg->pose.orientation.z;
        Eulerf euler(Quatf(_fms_in.INS_Out.quat));
        _fms_in.INS_Out.phi     = euler.phi();
        _fms_in.INS_Out.theta   = euler.theta();
        _fms_in.INS_Out.psi     = euler.psi();
        ROS_INFO("UAV %s: x_R: %f, y_R: %f, h_R: %f, phi: %f, theta: %f, psi: %f", _node_name.c_str(), _fms_in.INS_Out.x_R, _fms_in.INS_Out.y_R, _fms_in.INS_Out.h_R,
                M_RAD_TO_DEG * _fms_in.INS_Out.phi, M_RAD_TO_DEG * _fms_in.INS_Out.theta, M_RAD_TO_DEG * _fms_in.INS_Out.psi);
    });

    local_vel_sub = subscribe<geometry_msgs::TwistStamped>(_node_name + "/mavros/local_position/velocity_local", 10, [this](const geometry_msgs::TwistStamped::ConstPtr& msg){
        //ENU to NED
        _fms_in.INS_Out.vn = msg->twist.linear.y;
        _fms_in.INS_Out.ve = msg->twist.linear.x;
        _fms_in.INS_Out.vd = -msg->twist.linear.z;
        _fms_in.INS_Out.airspeed = std::sqrt(std::pow(_fms_in.INS_Out.vn, 2) + std::pow(_fms_in.INS_Out.ve, 2) + std::pow(_fms_in.INS_Out.vd, 2));
        ROS_INFO("UAV %s: vn: %f, ve: %f, vd: %f", _node_name.c_str(), _fms_in.INS_Out.vn, _fms_in.INS_Out.ve, _fms_in.INS_Out.vd);
    });

    ROS_INFO("UAV node %s created", name());

    _fms.initialize();
    return 0;
}

void UavNode::fms_step()
{
    fusion.cross.x_R[_uav_id] = _fms_in.INS_Out.x_R;
    fusion.cross.y_R[_uav_id] = _fms_in.INS_Out.y_R;
    fusion.cross.h_R[_uav_id] = _fms_in.INS_Out.h_R;
    fusion.cross.vn[_uav_id] = _fms_in.INS_Out.vn;
    fusion.cross.ve[_uav_id] = _fms_in.INS_Out.ve;
    fusion.cross.vd[_uav_id] = _fms_in.INS_Out.vd;
    fusion.cross.psi[_uav_id] = _fms_in.INS_Out.psi;
    
    _fms_in.Pilot_Cmd = {};
    _fms_in.Mission_Data = {};
    // _fms_in.INS_Out; AUTOMATICALLY UPDATED BY SUBSCRIBERS
    _fms_in.Formation_Cross = fusion.cross;
    _fms_out = _fms.step(&_fms_in);

    fusion.cross.left_time[_uav_id] = _fms_out.Form_Single;
    fusion.mission = _fms_out.Other_Mission_Data;
}
/**
 * @brief Publish a trajectory setpoint
 *        For this example, it sends a trajectory setpoint to make the
 *        vehicle hover at 5 meters with a yaw angle of 180 degrees.
 */
void UavNode::publish_trajectory_setpoint()
{
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
    */  //only control vn, ve, vh, an, ae
    setpoint.type_mask = mavros_msgs::PositionTarget::IGNORE_PX | mavros_msgs::PositionTarget::IGNORE_PY | mavros_msgs::PositionTarget::IGNORE_PZ | 
            mavros_msgs::PositionTarget::IGNORE_AFZ | mavros_msgs::PositionTarget::IGNORE_YAW | mavros_msgs::PositionTarget::IGNORE_YAW_RATE;
    //NED to ENU
    setpoint.velocity.y = -1;    //vn
    setpoint.velocity.x = 0;    //ve
    setpoint.velocity.z = 0.4;    //vh
    setpoint.acceleration_or_force.y = 0;    //an
    setpoint.acceleration_or_force.x = 0;    //ae
    setpoint_raw_local_pub.publish(setpoint);
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

int UavNode::call_once()
{
    if (!connected())
    {
        return 0;
    }

    fms_step();
    publish_offboard_control_mode();
    publish_trajectory_setpoint();
    return 0;
}

bool UavNode::connected() const
{
    return _state.connected;
}

const char* UavNode::name()
{
    return _node_name.c_str();
}