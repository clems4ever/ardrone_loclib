
#include <QCoreApplication>

#include "environmentengine.h"

#include "ros/ros.h"

int main(int argc, char **argv)
{
    ros::init(argc, argv, "ardrone_environment");
    QCoreApplication app(argc, argv);
    qDebug("ARDrone Environment starting...");
    EnvironmentEngine engine;
    engine.start();
    //qDebug("ARDrone Environment node is ending...");

    return app.exec();
}
