#include <ros/ros.h>
#include <vector>
#include <thread>
#include "uav_node.h"

static constexpr int NUM_UAVS = 3;

int main(int argc, char** argv) 
{
    ros::init(argc, argv, "Formation");

    std::vector<std::thread> threads;

    for (size_t i = 0; i < NUM_UAVS; i++)
    {
        threads.emplace_back([i](){
            std::shared_ptr<UavNode> uav = std::make_shared<UavNode>(i);
            if (uav->initialize() != 0)
            {
                ROS_ERROR("Failed to initialize %s", uav->name());
            }

            ros::Rate rate(200);
            while (1)
            {
                uav->call_once();
                rate.sleep();
            }
        });
    }

    ros::spin();
    
    for (auto &thread : threads)
    {
        thread.join();
    }

    return 0;
}