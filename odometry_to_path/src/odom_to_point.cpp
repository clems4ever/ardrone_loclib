#include "ros/ros.h"
#include "geometry_msgs/Pose.h"
#include "nav_msgs/Odometry.h"
#include "tf/transform_broadcaster.h"

ros::Publisher pointPub;

void odomCB(const nav_msgs::Odometry::ConstPtr& odom)
{
	geometry_msgs::Point pointMsg;

	pointMsg= odom->pose.pose.position;

	pointPub.publish(pointMsg);

	return;
}


int main(int argc, char *argv[])
{
	ros::init(argc,argv,"odom_to_point");
	ros::NodeHandle nh;

	pointPub=nh.advertise<geometry_msgs::Point>("point",10);

  ros::Subscriber sub = nh.subscribe("odom", 20, odomCB);
	
  ros::spin();

	return 0;
}
		
