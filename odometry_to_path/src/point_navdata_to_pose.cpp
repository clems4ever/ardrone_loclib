#include "ros/ros.h"
#include "geometry_msgs/Pose.h"
#include "geometry_msgs/Point.h"
#include "tf/transform_broadcaster.h"
#include "ardrone_autonomy/Navdata.h"
#define PI 3.141592653589793

ros::Publisher posePub;
geometry_msgs::Pose poseMsg;

void odomCB(const geometry_msgs::Point::ConstPtr& point)
{
	poseMsg.position.x = point->x;
	poseMsg.position.y = point->y;


	posePub.publish(poseMsg);

	return;
}

void navdataCB(const ardrone_autonomy::Navdata::ConstPtr& navdata){
	poseMsg.orientation.z = navdata->rotZ * PI/180.0; //converts to radians from degrees
	poseMsg.position.z=navdata->altd/700; //converts from mm from the navadata message to meters for standard use
}

int main(int argc, char *argv[])
{
	ros::init(argc,argv,"point_navdata_to_pose");
	ros::NodeHandle nh;

	posePub=nh.advertise<geometry_msgs::Pose>("/pose_estimation",10);

  ros::Subscriber sub = nh.subscribe("/kalman_position", 1, odomCB);
  ros::Subscriber sub_nav = nh.subscribe("/ardrone/navdata", 1, navdataCB);
	
  ros::spin();

	return 0;
}

