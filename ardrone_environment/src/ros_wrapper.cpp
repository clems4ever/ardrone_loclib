#include "ros_wrapper.h"

#include "ros/ros.h"

ros_wrapper::ros_wrapper(QObject *parent) :
    QObject(parent)
{
    ros::NodeHandle n;

    ros::ServiceServer service = n.advertiseService("add_two_ints", ros_wrapper::sendStaticMap);
    ROS_INFO("Ready to add two ints.");
    ros::spin();
}

bool ros_wrapper::sendStaticMap(ardrone_environment::ARDroneMap::Request &req, ardrone_environment::ARDroneMap::Response &res)
{
    return true;
}
