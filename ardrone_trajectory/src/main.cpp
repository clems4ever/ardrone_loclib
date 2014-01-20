
#include <QCoreApplication>

#include "ardrone_trajectory.h"

#include "ros/ros.h"

int main(int argc, char **argv)
{
    QCoreApplication app(argc, argv);
    ros::init(argc, argv, "ardrone_trajectory", ros::init_options::NoSigintHandler);
    ARDroneTrajectory engine;

    engine.start();

    return app.exec();
}
