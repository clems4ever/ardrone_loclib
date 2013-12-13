#ifndef ROS_WRAPPER_H
#define ROS_WRAPPER_H

#include <QObject>
#include <QThread>
#include "map2d.h"

#include "ardrone_environment/ARDroneMapSrv.h"

class ros_wrapper : public QThread
{
    Q_OBJECT
public:
    explicit ros_wrapper(QObject *parent = 0);

    void run();

    static void storeMap2D(Map2D *map);
    static bool sendStaticMap(ardrone_environment::ARDroneMapSrv::Request &req, ardrone_environment::ARDroneMapSrv::Response &res);
signals:

public slots:

private:
    static Map2D *p_map;
    bool m_isRunning;

};

#endif // ROS_WRAPPER_H
