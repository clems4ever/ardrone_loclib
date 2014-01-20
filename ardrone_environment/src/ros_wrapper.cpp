#include "ros_wrapper.h"

#include "environmentengine.h"

#include "opencv/cv.h"
#include "ros/ros.h"
#include "image_transport/image_transport.h"
#include "opencv/cvwimage.h"
#include "cv_bridge/CvBridge.h"

EnvironmentEngine* ros_wrapper::p_environment = 0;
ros::Publisher ros_wrapper::m_qrcode_position_pub;

ros_wrapper::ros_wrapper(QObject *parent) :
    QThread(parent)
{
    m_isRunning = true;
}

/** @brief thread function which is a ros loop that listens and publishes topics.
  */
void ros_wrapper::run()
{
    ros::NodeHandle n;
    image_transport::ImageTransport it(n);
    ros::Rate loop_rate(5);

    ros::ServiceServer s1 = n.advertiseService("ardrone_loclib_map", ros_wrapper::sendStaticMap);
    ros::ServiceServer s2 = n.advertiseService("ardrone_loclib_tags", ros_wrapper::sendTagList);
    m_missionServiceClient = n.serviceClient<ardrone_msgs::ARDroneTrajectorySrv>("ardrone_loclib_trajectory");

    image_transport::Publisher environmentPublisher = it.advertise("ardrone_loclib_image", 100);
    sensor_msgs::ImagePtr msg;

    ros::Subscriber su1 = n.subscribe("ardrone_loclib_mission", 1000, ros_wrapper::storeMission);

    // Deprecated version of locate drone (used by ardrone_simulator)
    ros::Subscriber su2 = n.subscribe("ardrone_loclib_position2d", 1000, ros_wrapper::locateDrone);
    ros::Subscriber KalmanPos_sub = n.subscribe("kalman_position", 1000, ros_wrapper::locateDroneFromKalman);
    ros::Subscriber qrcode_transform_sub = n.subscribe("qrcode", 1000, ros_wrapper::transformQRCode);
    m_qrcode_position_pub = n.advertise<geometry_msgs::Point>("tag_position", 100);
    QImage img;

    while(ros::ok()){
        if(p_environment != 0 && p_environment->ready())
        {
            p_environment->computeImage();
            img = QImage(p_environment->getImage());
            //qDebug(QString("%1,%2").arg(img.size().width()).arg(img.size().height()).toStdString().c_str());
            // Don't publish the message in ROS when the 2 lines are commented
            //msg = sensor_msgs::CvBridge::cvToImgMsg(img, "rgba8");
            //environmentPublisher.publish(msg);
            emit environmentImagePublished(img);
        }

        ros::spinOnce();

        loop_rate.sleep();

    }
}

/** @brief Ends the ros node
  */
void ros_wrapper::end()
{
    ros::shutdown();
}

/** @brief Stores a pointer on the environment engine in order to call methods when the wrapper receives data from ROS
  */
void ros_wrapper::storeEnvironmentEngine(EnvironmentEngine *env)
{
    ros_wrapper::p_environment = env;
}


/** @brief Sends a 2d array of the tiles composing the map (Wall or empty tile) on the ros bus
  *
  */
bool ros_wrapper::sendStaticMap(ardrone_msgs::ARDroneMapSrv::Request &req, ardrone_msgs::ARDroneMapSrv::Response &res)
{
    qDebug("sending back response");
    if(ros_wrapper::p_environment == 0) return true;

    int width = p_environment->getSize().width();
    int height = p_environment->getSize().height();
    res.map.tiles.resize(width);

    for(int x=0; x < width; x++)
    {
        res.map.tiles.at(x).x.resize(height);

        for(int y=0; y<height; y++)
        {
            res.map.tiles.at(x).x.at(y) = p_environment->getTile(x, y);
        }
    }
    res.map.scale = p_environment->getScale();
    res.map.offsetx = p_environment->getOffset().x();
    res.map.offsety = p_environment->getOffset().y();
    return true;
}

/** @brief Sends the list of the tags on the map
  *
  */
bool ros_wrapper::sendTagList(ardrone_msgs::ARDroneTagListSrv::Request &req, ardrone_msgs::ARDroneTagListSrv::Response &res)
{
    res.tagList.resize(p_environment->getTagsList().size());
    for(int i=0; i<p_environment->getTagsList().size(); i++)
    {
        EnvironmentEngine::Tag tag = p_environment->getTagsList().at(i);
        res.tagList.at(i).x = tag.x;
        res.tagList.at(i).y = tag.y;
    }

    return true;
}

/** @brief Callback called when the environment receives a path made of all the 2D points the drone will fly over to reach a target (the last point)
  *
  */
void ros_wrapper::storeMission(const ardrone_msgs::ARDroneMission::ConstPtr &mission)
{
    qDebug("Store mission callback");
    EnvironmentEngine::Path p;
    for(unsigned int i=0; i<mission->positions.size(); i++)
    {
        p.append(EnvironmentEngine::DoublePoint(mission->positions.at(i).x, mission->positions.at(i).y));
    }
    p_environment->setMission(p);
}

/** @brief Gets the drone position from the topic and refresh its position in the engine.
  */
void ros_wrapper::locateDrone(const ardrone_msgs::ARDronePosition2D::ConstPtr &msg)
{
    p_environment->updateDronePosition(msg->x, msg->y);
}


/** @brief Gets the drone position from the topic Ardrone_KalmanPos and refresh its position in the engine.
  */
void ros_wrapper::locateDroneFromKalman(const geometry_msgs::Point &msg)
{
    p_environment->updateDronePosition(msg.x, msg.y);
}

void ros_wrapper::transformQRCode(const std_msgs::String &msg)
{
    QList<EnvironmentEngine::Tag> l = p_environment->getTagsList();
    EnvironmentEngine::DoublePoint offset;
    for(int i=0; i<l.size(); i++)
    {
        EnvironmentEngine::Tag t = l.at(i);
        if(t.code == QString(msg.data.c_str()))
        {
            geometry_msgs::Point p;
            p.x = t.x + offset.x();
            p.y = t.y + offset.y();
            p.z = 0.0;
            m_qrcode_position_pub.publish(p);
        }
    }
}

void ros_wrapper::computeTrajectory()
{
    ardrone_msgs::ARDroneTrajectorySrv srv;
    int width = p_environment->getSize().width();
    int height = p_environment->getSize().height();
    srv.request.map.tiles.resize(width);

    for(int x=0; x < width; x++)
    {
        srv.request.map.tiles.at(x).x.resize(height);

        for(int y=0; y<height; y++)
        {
            srv.request.map.tiles.at(x).x.at(y) = p_environment->getTile(x, y);
        }
    }

    srv.request.map.scale = p_environment->getScale();
    srv.request.map.offsetx = p_environment->getOffset().x();
    srv.request.map.offsety = p_environment->getOffset().y();

    if(m_missionServiceClient.call(srv))
    {
        EnvironmentEngine::Path p;
        for(int i; i<srv.response.trajectory.points.size(); i++)
        {
            EnvironmentEngine::DoublePoint pt(srv.response.trajectory.points.at(i).x, srv.response.trajectory.points.at(i).y);
            p.append(pt);
        }
        p_environment->setMission(p);
    }
}

