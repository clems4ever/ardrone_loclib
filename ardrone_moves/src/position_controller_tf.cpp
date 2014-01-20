#include <stdio.h>                     /* This ert_main.c example uses printf/fflush */
#include "Pos_Controller.h"            /* Model's header file */
#include "rtwtypes.h"                    /* MathWorks types */

#include "ros/ros.h"
#include "geometry_msgs/PoseWithCovarianceStamped.h"
#include "geometry_msgs/Twist.h"
#include "nav_msgs/Odometry.h"
#include "ardrone_moves/SwitchOnOff.h"
#include <tf/transform_listener.h>


//#define DEBUG_POS_CONTROLLER_OUTPUTS
//use only if you have debug outputs in ert generated files
//see used fields of Pos_Controller_Y between #ifdef DEBUG_POS_CONTROLLER_OUTPUTS and #endif
#ifdef DEBUG_POS_CONTROLLER_OUTPUTS
#include "visualization_msgs/Marker.h"
#endif

static boolean_T OverrunFlag = 0;
bool _enabled=false;

ros::Publisher twistPublisher;
#ifdef DEBUG_POS_CONTROLLER_OUTPUTS
ros::Publisher epsPublisher;
ros::Publisher odomSpeedPublisher;
ros::Publisher vis_pub;
#endif

geometry_msgs::Twist twist;

void rt_OneStep(void)
{
  if (OverrunFlag++) {
    rtmSetErrorStatus(Pos_Controller_M, "Overrun");
    return;
  }
  Pos_Controller_step();
  OverrunFlag--;
}


bool setEnabled(ardrone_moves::SwitchOnOff::Request &req,
								ardrone_moves::SwitchOnOff::Response &res){
	_enabled=req.enable;
	if(_enabled){
		ROS_INFO("position tracking enabled");
	}else{
		ROS_INFO("position tracking disabled");
	}
	return true;
}

bool setRelativeYaw(ardrone_moves::SwitchOnOff::Request &req,
								ardrone_moves::SwitchOnOff::Response &res){
	if(req.enable){
		ROS_INFO("yaw command is relative to drone direction");
		Pos_Controller_U.yaw_is_relative=1;
	}else{
		ROS_INFO("yaw command is absolute in reference frame");
		Pos_Controller_U.yaw_is_relative=0;
	}
	return true;
}

void target_callback(const geometry_msgs::Pose::ConstPtr& consigne){
	Pos_Controller_U.consigne[0]=consigne->position.x;
	Pos_Controller_U.consigne[1]=consigne->position.y;
	Pos_Controller_U.consigne[2]=consigne->position.z;
	Pos_Controller_U.yaw_cons=consigne->orientation.z;
	ROS_DEBUG("new consigne : %f %f %f",Pos_Controller_U.consigne[0],Pos_Controller_U.consigne[1],Pos_Controller_U.consigne[2]);
}

void transform_callback(tf::StampedTransform transform){
	double roll,pitch,yaw;

	Pos_Controller_U.position[0]=transform.getOrigin().x();
	Pos_Controller_U.position[1]=transform.getOrigin().y();
	Pos_Controller_U.position[2]=transform.getOrigin().z();
	tf::Matrix3x3(transform.getRotation()).getRPY(roll,pitch,yaw);
	Pos_Controller_U.yaw=yaw;
	ROS_INFO("new position : %f %f %f %f",Pos_Controller_U.position[0],Pos_Controller_U.position[1],Pos_Controller_U.position[2], yaw);

}

void step_PID(void){
#ifdef DEBUG_POS_CONTROLLER_OUTPUTS
	visualization_msgs::Marker marker, marker_loc;
	nav_msgs::Odometry odomSpeed;
#endif
	if(_enabled){
		rt_OneStep();

		twist.linear.x=Pos_Controller_Y.speedcmd[0];
		twist.linear.y=Pos_Controller_Y.speedcmd[1];
		twist.linear.z=Pos_Controller_Y.speedcmd[2];
		twist.angular.z=Pos_Controller_Y.yawcmd;

#ifdef DEBUG_POS_CONTROLLER_OUTPUTS
		epsilon.position.x=-Pos_Controller_U.position[0]+Pos_Controller_U.consigne[0];
		epsilon.position.y=-Pos_Controller_U.position[1]+Pos_Controller_U.consigne[1];
		epsilon.position.z=-Pos_Controller_U.position[2]+Pos_Controller_U.consigne[2];

		//assert length are equals in absolute and drone speed
		real_T err=pow(Pos_Controller_Y.speedcmd[0],2)+pow(Pos_Controller_Y.speedcmd[1],2)-pow(Pos_Controller_Y.absolute_speedcmd[0],2)-pow(Pos_Controller_Y.absolute_speedcmd[1],2);
		if(err>0.00001 || err <-0.00001){
			ROS_ERROR("change rep wrong! %f",err);
		}

		//debug speed as odometry message
		odomSpeed.header.frame_id="/nav";
		odomSpeed.header.stamp=ros::Time::now();
		odomSpeed.pose.pose.position.x=Pos_Controller_U.position[0];
		odomSpeed.pose.pose.position.y=Pos_Controller_U.position[1];
		odomSpeed.pose.pose.position.z=Pos_Controller_U.position[2];

		odomSpeed.twist.twist.linear.x=Pos_Controller_Y.absolute_speedcmd[0];
		odomSpeed.pose.pose.position.y=Pos_Controller_Y.absolute_speedcmd[1];
		odomSpeed.pose.pose.position.z=Pos_Controller_Y.absolute_speedcmd[2];
		odomSpeedPublisher.publish(odomSpeed);

		{
			geometry_msgs::Point p;
			marker.header.frame_id = "nav";
			marker.header.stamp = ros::Time();
			marker.ns = "abs_speed_display";
			marker.id = 0;
			marker.type = visualization_msgs::Marker::ARROW;
			marker.action = visualization_msgs::Marker::ADD;
			p.x=Pos_Controller_U.position[0];
			p.y=Pos_Controller_U.position[1];
			p.z=Pos_Controller_U.position[2];
			marker.points.push_back(p);
			p.x=Pos_Controller_U.position[0]+Pos_Controller_Y.absolute_speedcmd[0]*10;
			p.y=Pos_Controller_U.position[1]+Pos_Controller_Y.absolute_speedcmd[1]*10;
			p.z=Pos_Controller_U.position[2]+Pos_Controller_Y.absolute_speedcmd[2]*0.2;
			marker.points.push_back(p);
			marker.scale.x=0.1;
			marker.scale.y=0.2;
			marker.color.g = 1.0f;
			marker.color.a = 1.0;
			vis_pub.publish( marker );


			marker_loc.header.frame_id = "/base_link";
			marker_loc.header.stamp = ros::Time();
			marker_loc.ns = "drone_speed_display";
			marker_loc.id = 0;
			marker_loc.type = visualization_msgs::Marker::ARROW;
			marker_loc.action = visualization_msgs::Marker::ADD;
			p.x=0;
			p.y=0;
			p.z=0;
			marker_loc.points.push_back(p);
			p.x=Pos_Controller_Y.speedcmd[0]*10;
			p.y=Pos_Controller_Y.speedcmd[1]*10;
			p.z=Pos_Controller_Y.speedcmd[2]*0.2;
			marker_loc.points.push_back(p);
			marker_loc.scale.x=0.1;
			marker_loc.scale.y=0.2;
			//marker_loc.scale.z=0.2;
			marker_loc.color.r = 0.7f;
			marker_loc.color.b = 0.7f;
			marker_loc.color.a = 1.0;
			vis_pub.publish( marker_loc );
		}
		epsPublisher.publish(epsilon);
#endif

		twistPublisher.publish(twist);
	}
}

int main(int argc,  char *argv[]){
	ros::init(argc,argv,"position_control");
	ros::NodeHandle nh("~");

	Pos_Controller_U.consigne[0]=0;
	Pos_Controller_U.consigne[1]=0;
	Pos_Controller_U.consigne[2]=1;
	Pos_Controller_U.yaw_cons=0;
	Pos_Controller_U.yaw_is_relative=0;

  /* Initialize model */
  Pos_Controller_initialize();

	ros::Subscriber consigneSubscriber = nh.subscribe("/position_target",1,target_callback);
	tf::TransformListener tf_listener;
	twistPublisher = nh.advertise<geometry_msgs::Twist>("/cmd_vel",1);
#ifdef DEBUG_POS_CONTROLLER_OUTPUTS
	epsPublisher = nh.advertise<geometry_msgs::Pose>("eps",1);
	vis_pub = nh.advertise<visualization_msgs::Marker>( "visualization_marker", 0 );
	odomSpeedPublisher = nh.advertise<nav_msgs::Odometry>("/absolute_speed_command",1);
#endif

	ros::ServiceServer enable_service = nh.advertiseService("enable",setEnabled);
	ros::ServiceServer switch_rel_yaw = nh.advertiseService("enable_relative_yaw",setRelativeYaw);

	ros::Rate rate(5.0);
  while (ros::ok() && rtmGetErrorStatus(Pos_Controller_M) == (NULL)) {
		if(_enabled){
			tf::StampedTransform transform;
			try{
				tf_listener.lookupTransform("/nav", "/base_link",
						ros::Time(0), transform);
			}
			catch (tf::TransformException ex){
				ROS_ERROR("%s",ex.what());
			}
			transform_callback(transform);
		}
		ros::spinOnce();
		step_PID();
		rate.sleep();
  }

  /* Terminate model */
  Pos_Controller_terminate();
  return 0;
}

