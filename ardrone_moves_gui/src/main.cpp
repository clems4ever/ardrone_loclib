#include <QtGui/QApplication>
#include "mainwindow.h"
#include "ros/ros.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ros::init(argc, argv, "pid_gui");
    ros::NodeHandle n;
    PositionCtrlGUI w(&n);

    w.show();
    
    return a.exec();
}
