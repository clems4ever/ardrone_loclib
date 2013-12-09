#ifndef ROS_WRAPPER_H
#define ROS_WRAPPER_H

#include <QObject>

#include <ardrone_environment/ARDroneMap.h>

class ros_wrapper : public QObject
{
    Q_OBJECT
public:
    explicit ros_wrapper(QObject *parent = 0);

    static bool sendStaticMap(ardrone_environment::ARDroneMap::Request &req, ardrone_environment::ARDroneMap::Response &res);
signals:

public slots:

};

#endif // ROS_WRAPPER_H
