
#include <QCoreApplication>

#include "environmentengine.h"

#include "ros/ros.h"

int main(int argc, char **argv)
{
    QCoreApplication app(argc, argv);
    ros::init(argc, argv, "ardrone_environment", ros::init_options::NoSigintHandler);
    qDebug("ARDrone Environment starting...");
    EnvironmentEngine engine;

    engine.start();
    //qDebug("ARDrone Environment node is ending...");

    return app.exec();
}
