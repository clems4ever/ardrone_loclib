#include "ros/ros.h"
#include "geometry_msgs/Pose.h"
#include "nav_msgs/Odometry.h"
#include "tf/transform_broadcaster.h"

ros::Publisher posePub;

void odomCB(const nav_msgs::Odometry::ConstPtr& odom)
{
	static tf::TransformBroadcaster tfBcaster;
	tf::Transform transf;

	transf.setOrigin( tf::Vector3(odom->pose.pose.position.x, odom->pose.pose.position.y, odom->pose.pose.position.z) );
	transf.setRotation( tf::Quaternion(0, 0, 0) );
	tfBcaster.sendTransform(tf::StampedTransform(transf, ros::Time::now(), odom->header.frame_id, "odom"));
	geometry_msgs::Pose poseMsg;

	poseMsg= odom->pose.pose;

	posePub.publish(poseMsg);

	return;
}


int main(int argc, char *argv[])
{
	ros::init(argc,argv,"odom_to_pose");
	ros::NodeHandle nh;

	posePub=nh.advertise<geometry_msgs::Pose>("pose",10);

  ros::Subscriber sub = nh.subscribe("odom", 20, odomCB);
	
  ros::spin();

	return 0;
}
		
