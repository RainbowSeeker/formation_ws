#pragma once

#include <ros/ros.h>
#include <mavros_msgs/CommandBool.h>
#include <mavros_msgs/SetMode.h>
#include <mavros_msgs/State.h>
#include <cstring>

#include "FMS_TECS/FMS.h"

#define FIXED_WING      1
#define AIRCRAFT_TYPE   FIXED_WING

static constexpr int CONTROL_PERIOD_HZ = 20;


class UavNode : public ros::NodeHandle
{
public:
    explicit UavNode(int uav_id);

    const char* name();
    int initialize();
    int spin();

    bool connected() const;
private:
    void parameter_update();
    void mission_decompose();
    void pilot_cmd_decode();
    void fms_step();
    void publish_trajectory_setpoint();
    void publish_offboard_control_mode();

    // ros publisher and subscriber
#if AIRCRAFT_TYPE == FIXED_WING
    ros::Publisher setpoint_raw_att_pub;   // publisher for Attitude setpoint.
#else
    ros::Publisher setpoint_raw_local_pub;  // publisher for Local position, velocity and acceleration setpoint.
#endif
    ros::Subscriber state_sub;
    ros::ServiceClient arming_client;
    ros::ServiceClient set_mode_client;
    uint32_t run_time_ms{0};

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