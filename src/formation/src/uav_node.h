#pragma once

#include <ros/ros.h>
#include <mavros_msgs/CommandBool.h>
#include <mavros_msgs/CommandInt.h>
#include <mavros_msgs/CommandTOL.h>
#include <mavros_msgs/SetMode.h>
#include <mavros_msgs/State.h>
#include <cstring>
#include <fstream>
#include <model/FMS_TECS/FMS.h>
#include <lib/matrix/math.hpp>
#include <lib/geo/geo.h>

#define FIXED_WING      1
#define AIRCRAFT_TYPE   FIXED_WING

static constexpr int CONTROL_PERIOD_HZ = 50;
static constexpr int CONTROL_PERIOD_MS = 1000 / CONTROL_PERIOD_HZ;

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
    void data_save();
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
    ros::ServiceClient cmd_client;
    ros::ServiceClient takeoff_client;
    uint32_t run_time_ms{0};

    int _uav_id;
    std::string _node_name;
    mavros_msgs::State _state;
    mavros_msgs::SetMode _set_mode;
    mavros_msgs::CommandBool _arm_cmd;
    mavros_msgs::CommandInt  _int_cmd;
    mavros_msgs::CommandTOL _takeoff_cmd;
    bool lat0_has_set{false};

    //FMS INPUT subscriber
    ros::Subscriber local_position_sub;
    ros::Subscriber global_position_sub;

    // FMS
    FMS _fms;
    FMS_In _fms_in;
    FMS_Out _fms_out;
    struct fms_fusion
    {
        MapProjection map;
        float ref_alt;
        Formation_Cross_Bus cross;
        Other_Mission_Data_Bus mission;
    };
    static fms_fusion fusion;


    //log
    std::ofstream _log_file;
    uint32_t _write_count{0};
};