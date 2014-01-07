
#include <QApplication>

#include "ardroneenvironment.h"

#include "ros/ros.h"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    QApplication::setQuitOnLastWindowClosed(false);
    ros::init(argc, argv, "ardrone_environment", ros::init_options::NoSigintHandler);
    qDebug("ARDrone Environment starting...");
    ARDroneEnvironment ardroneEnvironment;
    ardroneEnvironment.start();


    //qDebug("ARDrone Environment node is ending...");

    return app.exec();
}
