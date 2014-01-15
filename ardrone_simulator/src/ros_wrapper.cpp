#include "ros_wrapper.h"

#include "ros/ros.h"
#include "simulatorengine.h"

#include "ardrone_environment/ARDroneMapSrv.h"
#include "ardrone_environment/ARDroneMission.h"


ros_wrapper::ros_wrapper(SimulatorEngine *simu, QObject *parent) :
    QThread(parent)
{
    p_simulator = simu;
}

void ros_wrapper::run()
{
    ros::NodeHandle n;
    ros::Rate loop_rate(20);

    ros::Publisher positionPublisher = n.advertise<ardrone_environment::ARDronePosition2D>("ardrone_loclib_position2d", 1000);
    ros::Publisher missionPublisher = n.advertise<ardrone_environment::ARDroneMission>("ardrone_loclib_mission", 1000);
    ros::ServiceClient mapClient = n.serviceClient<ardrone_environment::ARDroneMapSrv>("ardrone_loclib_map");
    ardrone_environment::ARDronePosition2D msg;
    ardrone_environment::ARDroneMapSrv srv;

    mapClient.call(srv);

    int xmax = srv.response.map.tiles.size();
    int ymax = srv.response.map.tiles.at(0).x.size();
    SimulatorEngine::Tile **map = p_simulator->createMap(srv.response.map.tiles.size(), srv.response.map.tiles.at(0).x.size());
    qDebug(QString("Size = %1x%2").arg(srv.response.map.tiles.size()).arg(srv.response.map.tiles.at(0).x.size()).toStdString().c_str());

    for(unsigned int x=0; x<srv.response.map.tiles.size(); x++)
    {
        for(unsigned int y=0; y<srv.response.map.tiles.at(x).x.size(); y++)
        {
            map[x][y].type = (SimulatorEngine::TileType)srv.response.map.tiles.at(x).x.at(y);
        }
    }

    srand(time(NULL));

    while(ros::ok()){

        int x1, y1;
        do
        {
            x1 = rand() % xmax;
            y1 = rand() % ymax;
        }while(map[x1][y1].type != SimulatorEngine::EMPTY);

        int x2 = rand() % xmax;
        int y2 = rand() % ymax;
        QList<QPoint> path = p_simulator->getPath(QPoint(x1,y1), QPoint(x2, y2));
        ardrone_environment::ARDroneMission mission;
        const double SCALEX = 0.78;
        const double SCALEY = 0.78;
        mission.positions.resize(path.size());
        for(int i=0; i<path.size(); i++)
        {
            mission.positions.at(i).x = ((double)path.at(i).x()) * SCALEX + 200.0;
            mission.positions.at(i).y = ((double)path.at(i).y()) * SCALEY + 200.0;
        }
        qDebug("Path published");

        sleep(2);
        missionPublisher.publish(mission);
        sleep(1);

        for(int j=0; j<path.size(); j++)
        {
            ros::spinOnce();

            double cx = mission.positions.at(j).x;
            double cy = mission.positions.at(j).y;

            msg.x = cx;
            msg.y = cy;

            positionPublisher.publish(msg);

            loop_rate.sleep();
        }
    }
}

