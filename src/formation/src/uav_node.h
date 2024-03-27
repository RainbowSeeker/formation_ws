#pragma once

#include <ros/ros.h>
#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/Vector3Stamped.h>
#include <mavros_msgs/CommandBool.h>
#include <mavros_msgs/SetMode.h>
#include <mavros_msgs/State.h>
#include <sensor_msgs/NavSatFix.h>
#include <cstring>

#include "FMS.h"

class UavNode : public ros::NodeHandle
{
public:
    explicit UavNode(int uav_id);

    const char* name();
    int initialize();
    int call_once();

    bool connected() const;
private:
    void fms_step();
    void publish_trajectory_setpoint();
    void publish_offboard_control_mode();

    // ros publisher and subscriber
    ros::Publisher setpoint_accel_pub;  // publisher for lateral acceleration (for loiter)
    ros::Publisher local_pos_pub;       // publisher for local position setpoint (including x_R y_R h_R)

    ros::Subscriber state_sub;
    ros::ServiceClient arming_client;
    ros::ServiceClient set_mode_client;

    int _uav_id;
    std::string _node_name;
    mavros_msgs::State _state;
    mavros_msgs::SetMode _set_mode;
    mavros_msgs::CommandBool _arm_cmd;


    // FMS
    FMS _fms;
    FMS_In _fms_in;
    FMS_Out _fms_out;
};