#include "ros/ros.h"
#include "geometry_msgs/Pose.h"
#include "nav_msgs/Odometry.h"
#include "tf/transform_broadcaster.h"
#include "ardrone_autonomy/Navdata.h"
#define PI 3.141592653589793

ros::Publisher posePub;
geometry_msgs::Pose poseMsg;

void odomCB(const nav_msgs::Odometry::ConstPtr& odom)
{
	static tf::TransformBroadcaster tfBcaster;
	tf::Transform transf;

	transf.setOrigin( tf::Vector3(odom->pose.pose.position.x, odom->pose.pose.position.y, odom->pose.pose.position.z) );
	transf.setRotation( tf::Quaternion(0, 0, 0) );
	tfBcaster.sendTransform(tf::StampedTransform(transf, ros::Time::now(), odom->header.frame_id, "odom"));

	poseMsg.position.x = odom->pose.pose.position.x;
	poseMsg.position.y = odom->pose.pose.position.y;


	posePub.publish(poseMsg);

	return;
}

void navdataCB(const ardrone_autonomy::Navdata::ConstPtr& navdata){
	poseMsg.orientation.z = navdata->rotZ * PI/180.0; //converts to radians from degrees
	poseMsg.position.z=navdata->altd/700; //converts from mm from the navadata message to meters for standard use
	posePub.publish(poseMsg);
}

int main(int argc, char *argv[])
{
	ros::init(argc,argv,"gps_navdata_to_pose");
	ros::NodeHandle nh;

	posePub=nh.advertise<geometry_msgs::Pose>("pose",10);

  ros::Subscriber sub = nh.subscribe("/gps_odom", 1, odomCB);
  ros::Subscriber sub_nav = nh.subscribe("/ardrone/navdata", 1, navdataCB);
	
  ros::spin();

	return 0;
}

