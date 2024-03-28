#pragma once

#include <ros/ros.h>
#include <mavros_msgs/CommandBool.h>
#include <mavros_msgs/SetMode.h>
#include <mavros_msgs/State.h>
#include <cstring>

#include "Formation_FMS/FMS.h"

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
    ros::Publisher setpoint_raw_local_pub;  // publisher for Local position, velocity and acceleration setpoint.

    ros::Subscriber state_sub;
    ros::ServiceClient arming_client;
    ros::ServiceClient set_mode_client;

    int _uav_id;
    std::string _node_name;
    mavros_msgs::State _state;
    mavros_msgs::SetMode _set_mode;
    mavros_msgs::CommandBool _arm_cmd;

    //FMS INPUT subscriber
    ros::Subscriber local_pose_sub;
    ros::Subscriber local_vel_sub;

    // FMS
    FMS _fms;
    FMS_In _fms_in;
    FMS_Out _fms_out;
    struct fms_fusion
    {
        Formation_Cross_Bus cross;
        Other_Mission_Data_Bus mission;
    };
    static fms_fusion fusion;
};