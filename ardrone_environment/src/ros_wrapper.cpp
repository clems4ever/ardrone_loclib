#include "ros_wrapper.h"

#include "ros/ros.h"
#include "image_transport/image_transport.h"
#include "opencv/cvwimage.h"
#include "cv_bridge/CvBridge.h"

Map2D* ros_wrapper::p_map = 0;

ros_wrapper::ros_wrapper(QObject *parent) :
    QThread(parent)
{

    m_isRunning = true;
}

void ros_wrapper::run()
{
    ros::NodeHandle n;
    image_transport::ImageTransport it(n);
    ros::Rate loop_rate(10);

    ros::ServiceServer service = n.advertiseService("ardrone_environment_provider", ros_wrapper::sendStaticMap);
    image_transport::Publisher environmentPublisher = it.advertise("ardrone_environment_image", 1);
    sensor_msgs::ImagePtr msg;

    ROS_INFO("Node is ready.");
    while(ros::ok()){
        ros::spinOnce();
        if(p_map != 0)
            msg = sensor_msgs::CvBridge::cvToImgMsg(p_map->getCvImage(), "rgba8");

        environmentPublisher.publish(msg);

        loop_rate.sleep();

    }
}

void ros_wrapper::storeMap2D(Map2D *map)
{
    ros_wrapper::p_map = map;
}

bool ros_wrapper::sendStaticMap(ardrone_environment::ARDroneMapSrv::Request &req, ardrone_environment::ARDroneMapSrv::Response &res)
{
    ROS_INFO("sending back response");
    if(ros_wrapper::p_map == 0) return true;

    int width = p_map->getSize().width();
    int height = p_map->getSize().height();
    res.map.tiles.resize(width);
    res.map.name = "INSA map";

    for(int x=0; x < width; x++)
    {
        res.map.tiles.at(x).x.resize(height);

        for(int y=0; y<height; y++)
        {
            res.map.tiles.at(x).x.at(y) = p_map->getTile(x, y).type;
        }
    }

    return true;
}

