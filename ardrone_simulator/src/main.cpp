
#include <QCoreApplication>

#include "simulatorengine.h"

#include "ros/ros.h"

int main(int argc, char **argv)
{
    QCoreApplication app(argc, argv);
    ros::init(argc, argv, "ardrone_simulator", ros::init_options::NoSigintHandler);
    qDebug("ARDrone Simulator starting...");
    SimulatorEngine engine;

    engine.start();
    //qDebug("ARDrone Environment node is ending...");

    return app.exec();
}
