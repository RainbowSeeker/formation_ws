#include "uav_node.h"

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

    setpoint_accel_pub = advertise<geometry_msgs::Vector3Stamped>(_node_name + "/mavros/setpoint_accel/accel", 10);
    local_pos_pub = advertise<geometry_msgs::PoseStamped>(_node_name + "/mavros/setpoint_position/local", 10);

    arming_client = serviceClient<mavros_msgs::CommandBool>(_node_name + "/mavros/cmd/arming");
    set_mode_client = serviceClient<mavros_msgs::SetMode>(_node_name + "/mavros/set_mode");

    ROS_INFO("UAV node %s created", name());

    _fms.initialize();
    return 0;
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

void UavNode::fms_step()
{
    _fms_out = _fms.step(&_fms_in);
}
/**
 * @brief Publish a trajectory setpoint
 *        For this example, it sends a trajectory setpoint to make the
 *        vehicle hover at 5 meters with a yaw angle of 180 degrees.
 */
void UavNode::publish_trajectory_setpoint()
{
	geometry_msgs::PoseStamped pose;
    pose.pose.position.x = 1000;
    pose.pose.position.y = 1000;
    pose.pose.position.z = 100;
    local_pos_pub.publish(pose);
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