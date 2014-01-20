#ifndef ROS_WRAPPER_H
#define ROS_WRAPPER_H

#include <QObject>
#include <QThread>

class ARDroneTrajectory;

#include "ardrone_environment/ARDronePosition2D.h"
#include "ardrone_environment/ARDroneMapSrv.h"

class ros_wrapper : public QThread
{
    Q_OBJECT
public:
    ros_wrapper(ARDroneTrajectory *simu, QObject *parent = 0);

    void run();

signals:

public slots:

private:
    bool m_isRunning;

    ARDroneTrajectory *p_simulator;

};

#endif // ROS_WRAPPER_H
