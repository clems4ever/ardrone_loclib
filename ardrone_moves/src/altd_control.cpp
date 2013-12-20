#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "ardrone_autonomy/Navdata.h"
#include "PID.hpp"

#include <sstream>

double consigne = 1;
double measure=0;
bool enabled=true;

void navdataCB(const ardrone_autonomy::Navdata::ConstPtr& navdata)
{
	measure=navdata->altd/1000; //convert to meters
	ROS_INFO("alt:%f\n",measure);
}

int main(int argc, char **argv)
{
	ros::init(argc, argv, "alt_control");

	ros::NodeHandle n;

	ros::Publisher twist_pub = n.advertise<geometry_msgs::Twist>("/cmd_vel", 100);
	ros::Subscriber navdata_sub = n.subscribe("/ardrone/navdata",100,navdataCB);

	ros::Duration(2).sleep();

	ros::Rate loop_rate(200.0);
	//ros::Rate loop_rate(0.005);
	PID pidctrl(0.25,0.003,0.3, 0.005, -1,1);

	geometry_msgs::Twist speeds;

	while (ros::ok())
	{
		if(enabled){
			speeds.linear.z=pidctrl.step(consigne,measure);
			twist_pub.publish(speeds);
		}

		ros::spinOnce();

		loop_rate.sleep();
	}
	return 0;
}

