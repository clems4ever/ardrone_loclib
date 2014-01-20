#ifndef ROS_WRAPPER_H
#define ROS_WRAPPER_H

#include <QObject>
#include <QThread>
#include <QImage>

#include "opencv/cv.h"

#include "ros/ros.h"

#include "ardrone_msgs/ARDroneMapSrv.h"
#include "ardrone_msgs/ARDroneTagListSrv.h"
#include "ardrone_msgs/ARDronePosition2D.h"
#include "ardrone_msgs/ARDroneMission.h"

#include "ardrone_msgs/ARDroneTrajectorySrv.h"

#include "geometry_msgs/Point.h"
#include "std_msgs/String.h"

class EnvironmentEngine;

class ros_wrapper : public QThread
{
    Q_OBJECT
public:
    explicit ros_wrapper(QObject *parent = 0);

    void run();

    void end();

    static void storeEnvironmentEngine(EnvironmentEngine *environment);
    static bool sendStaticMap(ardrone_msgs::ARDroneMapSrv::Request &req, ardrone_msgs::ARDroneMapSrv::Response &res);
    static bool sendTagList(ardrone_msgs::ARDroneTagListSrv::Request &req, ardrone_msgs::ARDroneTagListSrv::Response &res);

    static void storeMission(const ardrone_msgs::ARDroneMission::ConstPtr& mission);
    static void locateDrone(const ardrone_msgs::ARDronePosition2D::ConstPtr& msg);
    static void locateDroneFromKalman(const geometry_msgs::Point& msg);

    static void transformQRCode(const std_msgs::String& msg);

    void computeTrajectory();

signals:
    void environmentImagePublished(QImage);

public slots:

private:
    static EnvironmentEngine *p_environment;
    bool m_isRunning;

    static ros::Publisher m_qrcode_position_pub;
    ros::ServiceClient m_missionServiceClient;

};

#endif // ROS_WRAPPER_H
