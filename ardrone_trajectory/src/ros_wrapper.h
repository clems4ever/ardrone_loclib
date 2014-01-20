#ifndef ROS_WRAPPER_H
#define ROS_WRAPPER_H

#include <QObject>
#include <QThread>

class ARDroneTrajectory;

#include "ardrone_msgs/ARDronePosition2D.h"
#include "ardrone_msgs/ARDroneMapSrv.h"

#include "ardrone_msgs/ARDroneTrajectory.h"
#include "ardrone_msgs/ARDroneTrajectorySrv.h"

class ros_wrapper : public QThread
{
    Q_OBJECT
public:
    ros_wrapper(ARDroneTrajectory *simu, QObject *parent = 0);

    void run();

    static bool computeTrajectory(ardrone_msgs::ARDroneTrajectorySrv::Request &req, ardrone_msgs::ARDroneTrajectorySrv::Response &resp);

signals:

public slots:

private:
    bool m_isRunning;
    static ARDroneTrajectory *p_trajectory;

};

#endif // ROS_WRAPPER_H
