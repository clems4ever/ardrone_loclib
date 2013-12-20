
#include <stdio.h>                     /* This ert_main.c example uses printf/fflush */
#include "Pos_Controller.h"            /* Model's header file */
#include "rtwtypes.h"                    /* MathWorks types */

#include <ros/ros.h>
#include <geometry_msgs/PoseWithCovarianceStamped.h>
#include <geometry_msgs/Twist.h>
#include "ardrone_moves/EnableController.h"
#include <tf/tf.h>

static boolean_T OverrunFlag = 0;
bool _enabled=false;

ros::Publisher twistPublisher;

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

bool setEnabled(ardrone_moves::EnableController::Request &req,
								ardrone_moves::EnableController::Response &res){
	_enabled=req.enable;
	if(_enabled){
		ROS_INFO("position tracking enabled");
	}else{
		ROS_INFO("position tracking disabled");
	}
	return true;
}


void target_callback(const geometry_msgs::Pose::ConstPtr& consigne){
	Pos_Controller_U.consigne[0]=consigne->position.x;
	Pos_Controller_U.consigne[1]=consigne->position.y;
	Pos_Controller_U.consigne[2]=consigne->position.z;
}

void pose_callback(const geometry_msgs::PoseWithCovarianceStamped::ConstPtr&	pose){

	double roll,pitch,yaw;

	if(_enabled){
		Pos_Controller_U.position[0]=pose->pose.pose.position.x;
		Pos_Controller_U.position[1]=pose->pose.pose.position.y;
		Pos_Controller_U.position[2]=pose->pose.pose.position.z;
		tf::Matrix3x3(tf::Quaternion(pose->pose.pose.orientation.x,pose->pose.pose.orientation.y,pose->pose.pose.orientation.z,pose->pose.pose.orientation.w)).getRPY(roll,pitch,yaw);
		Pos_Controller_U.yaw=yaw;

		rt_OneStep();

		twist.linear.x=Pos_Controller_Y.speedcmd[0];
		twist.linear.y=Pos_Controller_Y.speedcmd[1];
		twist.linear.z=Pos_Controller_Y.speedcmd[2];
		twist.angular.z=Pos_Controller_Y.yawcmd;

		twistPublisher.publish(twist);
	}
}

int main(int argc,  char *argv[]){
	ros::init(argc,argv,"position_control");
	ros::NodeHandle nh("~");

	Pos_Controller_U.consigne[0]=0;
	Pos_Controller_U.consigne[1]=0;
	Pos_Controller_U.consigne[2]=0;
	Pos_Controller_U.yaw_cons=0;
	_enabled=false;

  /* Initialize model */
  Pos_Controller_initialize();

	ros::Subscriber positionSubscriber = nh.subscribe("/pose_estimation",1,pose_callback);
	ros::Subscriber consigneSubscriber = nh.subscribe("/position_target",1,target_callback);
	twistPublisher = nh.advertise<geometry_msgs::Twist>("/cmd_vel",1);

	ros::ServiceServer enable_service = nh.advertiseService("enable",setEnabled);

  while (ros::ok() && rtmGetErrorStatus(Pos_Controller_M) == (NULL)) {
		ros::spinOnce();
  }

  /* Terminate model */
  Pos_Controller_terminate();
  return 0;
}

