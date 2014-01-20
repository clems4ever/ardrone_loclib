#include "ros_wrapper.h"
#include "ardrone_trajectory.h"

#include <QPoint>

#include "ros/ros.h"

#include "ardrone_msgs/ARDroneMapSrv.h"
#include "ardrone_msgs/ARDroneMission.h"

#include "ardrone_msgs/ARDroneTrajectory.h"
#include "ardrone_msgs/ARDroneTrajectorySrv.h"


ARDroneTrajectory *ros_wrapper::p_trajectory = 0;


ros_wrapper::ros_wrapper(ARDroneTrajectory *simu, QObject *parent) :
    QThread(parent)
{
    p_trajectory = simu;
}

void ros_wrapper::run()
{
    ros::NodeHandle n;
    ros::Rate loop_rate(1);

    ros::ServiceServer s2 = n.advertiseService("ardrone_loclib_trajectory", ros_wrapper::computeTrajectory);

    while(1)
    {
        ros::spinOnce();
        loop_rate.sleep();
        //qDebug("Sleep");
    }
}


bool ros_wrapper::computeTrajectory(ardrone_msgs::ARDroneTrajectorySrv::Request &req, ardrone_msgs::ARDroneTrajectorySrv::Response &resp)
{
    qDebug("Compute trajectory");
    int xmax = req.map.tiles.size();
    int ymax = req.map.tiles.at(0).x.size();
    ARDroneTrajectory::Tile **map = p_trajectory->createMap(req.map.tiles.size(), req.map.tiles.at(0).x.size());
    double scale = req.map.scale;
    double offsetx = req.map.offsetx;
    double offsety = req.map.offsety;
    QPoint pt1(req.p1.x, req.p1.y), pt2(req.p2.x, req.p2.y);

    for(int x=0; x<xmax; x++)
    {
        for(int y=0; y<ymax; y++)
        {
            map[x][y].type = (ARDroneTrajectory::TileType)req.map.tiles.at(x).x.at(y);
        }
    }

    QList<QPoint> path = p_trajectory->getPath(pt1, pt2);
    resp.trajectory.points.resize(path.size());
    for(int i=0; i<path.size(); i++)
    {
        resp.trajectory.points.at(i).x = ((double)path.at(i).x()) * scale + offsetx;
        resp.trajectory.points.at(i).y = -((double)path.at(i).y() - p_trajectory->getSize().height()) * scale + offsety;
    }

    return true;
}
