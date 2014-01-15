#ifndef ROS_WRAPPER_H
#define ROS_WRAPPER_H

#include <QObject>
#include <QThread>

#include "opencv/cv.h"

#include "ardrone_environment/ARDroneMapSrv.h"
#include "ardrone_environment/ARDroneTagListSrv.h"
#include "ardrone_environment/ARDronePosition2D.h"
#include "ardrone_environment/ARDroneMission.h"

class EnvironmentEngine;

class ros_wrapper : public QThread
{
    Q_OBJECT
public:
    explicit ros_wrapper(QObject *parent = 0);

    void run();

    void end();

    static void storeEnvironmentEngine(EnvironmentEngine *environment);
    static bool sendStaticMap(ardrone_environment::ARDroneMapSrv::Request &req, ardrone_environment::ARDroneMapSrv::Response &res);
    static bool sendTagList(ardrone_environment::ARDroneTagListSrv::Request &req, ardrone_environment::ARDroneTagListSrv::Response &res);

    static void storeMission(const ardrone_environment::ARDroneMission::ConstPtr& mission);
    static void locateDrone(const ardrone_environment::ARDronePosition2D::ConstPtr& msg);

signals:
    void environmentImagePublished(IplImage *);

public slots:

private:
    static EnvironmentEngine *p_environment;
    bool m_isRunning;

};

#endif // ROS_WRAPPER_H
