#include <stdio.h>                     /* This ert_main.c example uses printf/fflush */
#include "Pos_Controller.h"            /* Model's header file */
#include "rtwtypes.h"                    /* MathWorks types */

#include <ros/ros.h>
#include <geometry_msgs/Pose.h>
#include <geometry_msgs/Twist.h>
#include "ardrone_moves/SwitchOnOff.h"
#include "ardrone_moves/ControllerState.h"
#include "ardrone_msgs/ARDroneTrajectory.h"
#include <tf/tf.h>


//#define DEBUG_POS_CONTROLLER_OUTPUTS
//use only if you have debug outputs in ert generated files
//see used fields of Pos_Controller_Y between #ifdef DEBUG_POS_CONTROLLER_OUTPUTS and #endif
#ifdef DEBUG_POS_CONTROLLER_OUTPUTS
#include "visualization_msgs/Marker.h"
#endif

#define DEFAULT_DISTANCE_THRESHOLD 1.0

#define PI 3.1415926535897931

static boolean_T OverrunFlag = 0;
bool _enabled=false;

ros::Publisher twistPublisher;
ros::Publisher epsPublisher;
#ifdef DEBUG_POS_CONTROLLER_OUTPUTS
ros::Publisher odomSpeedPublisher;
ros::Publisher vis_pub;
#endif

double distance_threshold;
std::vector<geometry_msgs::Point> trajectory_plan;

geometry_msgs::Twist twist;

double distance(double pos1[],double pos2[]);

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

bool getState(ardrone_moves::ControllerState::Request &req,
							ardrone_moves::ControllerState::Response &res){
	geometry_msgs::Pose epsilon;
	geometry_msgs::Pose target;
	res.target_reached=(distance(Pos_Controller_U.position,Pos_Controller_U.consigne)<distance_threshold);
	res.active=_enabled;
	epsilon.position.x=-Pos_Controller_U.position[0]+Pos_Controller_U.consigne[0];
	epsilon.position.y=-Pos_Controller_U.position[1]+Pos_Controller_U.consigne[1];
	epsilon.position.z=-Pos_Controller_U.position[2]+Pos_Controller_U.consigne[2];
	epsilon.orientation.z=Pos_Controller_U.yaw_cons-Pos_Controller_U.yaw;
	res.epsilon=epsilon;
	target.position.x=Pos_Controller_U.consigne[0];
	target.position.y=Pos_Controller_U.consigne[1];
	target.position.z=Pos_Controller_U.consigne[2];
	target.orientation.z=Pos_Controller_U.yaw_cons;
	res.current_target=target;
	res.relative_yaw=Pos_Controller_U.yaw_is_relative;
	return true;
}

void target_callback(const geometry_msgs::Pose::ConstPtr& consigne){
	Pos_Controller_U.consigne[0]=consigne->position.x;
	Pos_Controller_U.consigne[1]=consigne->position.y;
	Pos_Controller_U.consigne[2]=consigne->position.z;
	Pos_Controller_U.yaw_cons=consigne->orientation.z+PI/2;
	trajectory_plan.clear();//clear the trajectory plan
	ROS_DEBUG("new consigne : %f %f %f",Pos_Controller_U.consigne[0],Pos_Controller_U.consigne[1],Pos_Controller_U.consigne[2]);
}

void trajectory_plan_callback(const ardrone_msgs::ARDroneTrajectory::ConstPtr& traj_plan){
	Pos_Controller_U.consigne[0]=traj_plan->points.begin()->x;
	Pos_Controller_U.consigne[1]=traj_plan->points.begin()->y;
	Pos_Controller_U.consigne[2]=traj_plan->points.begin()->z;
	trajectory_plan.assign(traj_plan->points.begin()+1,traj_plan->points.end());//copy remaining elements
	Pos_Controller_U.yaw_cons=0;
	Pos_Controller_U.yaw_is_relative=1;
	ROS_DEBUG("new set point : %f %f %f",Pos_Controller_U.consigne[0],Pos_Controller_U.consigne[1],Pos_Controller_U.consigne[2]);
}

void pose_callback(const geometry_msgs::Pose::ConstPtr&	pose){

	double roll,pitch,yaw;

		Pos_Controller_U.position[0]=pose->position.x;
		Pos_Controller_U.position[1]=pose->position.y;
		Pos_Controller_U.position[2]=pose->position.z;
		//tf::Matrix3x3(tf::Quaternion(pose->orientation.x,pose->orientation.y,pose->orientation.z,pose->orientation.w)).getRPY(roll,pitch,yaw);
		//ROS_DEBUG("orientation RPY : %f %f %f",roll,pitch,yaw);
		Pos_Controller_U.yaw=pose->orientation.z+PI/2;
		//TODO :Pos_Controller_U.yaw=yaw+PI/2;

}

double distance(double pos1[],double pos2[]){
	double dist=0;
	dist = sqrt ( pow(pos2[0]-pos1[0],2) + pow(pos2[1]-pos1[1],2)+ pow(pos2[2]-pos1[2],2)  );
	return dist;
}

void update_target(void){
	if(trajectory_plan.size()==0){
		return; //nothing to do
	}
	if(distance(Pos_Controller_U.position,Pos_Controller_U.consigne)<distance_threshold){
		Pos_Controller_U.consigne[0]=trajectory_plan.begin()->x;
		Pos_Controller_U.consigne[1]=trajectory_plan.begin()->y;
		Pos_Controller_U.consigne[2]=trajectory_plan.begin()->z;
		trajectory_plan.erase(trajectory_plan.begin());
		ROS_DEBUG("updated set point : %f %f %f",Pos_Controller_U.consigne[0],Pos_Controller_U.consigne[1],Pos_Controller_U.consigne[2]);
	}
}

void step_PID(void){
#ifdef DEBUG_POS_CONTROLLER_OUTPUTS
	visualization_msgs::Marker marker, marker_loc;
	nav_msgs::Odometry odomSpeed;
#endif
	geometry_msgs::Pose epsilon;
	if(_enabled){

		update_target();//update the target to the next point if the current one is reached
		
		rt_OneStep();

		twist.linear.x=Pos_Controller_Y.speedcmd[0];
		twist.linear.y=Pos_Controller_Y.speedcmd[1];
		twist.linear.z=Pos_Controller_Y.speedcmd[2];
		twist.angular.z=Pos_Controller_Y.yawcmd;

		epsilon.position.x=-Pos_Controller_U.position[0]+Pos_Controller_U.consigne[0];
		epsilon.position.y=-Pos_Controller_U.position[1]+Pos_Controller_U.consigne[1];
		epsilon.position.z=-Pos_Controller_U.position[2]+Pos_Controller_U.consigne[2];
		epsilon.orientation.z=Pos_Controller_U.yaw_cons-Pos_Controller_U.yaw;
#ifdef DEBUG_POS_CONTROLLER_OUTPUTS

		//assert length are equals in absolute and drone speed
		real_T err=pow(Pos_Controller_Y.speedcmd[0],2)+pow(Pos_Controller_Y.speedcmd[1],2)-pow(Pos_Controller_Y.absolute_speedcmd[0],2)-pow(Pos_Controller_Y.absolute_speedcmd[1],2);
		if(err>0.00001 || err <-0.00001)
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
#endif
		epsPublisher.publish(epsilon);

		twistPublisher.publish(twist);
	}
}

int main(int argc,  char *argv[]){
	ros::init(argc,argv,"position_control");
	ros::NodeHandle nh("~");

	

  /* Initialize model */
  Pos_Controller_initialize();

	Pos_Controller_U.consigne[0]=0;
	Pos_Controller_U.consigne[1]=0;
	Pos_Controller_U.consigne[2]=1;
	Pos_Controller_U.yaw_cons=+PI/2;
	Pos_Controller_U.yaw_is_relative=0;
	Pos_Controller_U.position[0]=0;
	Pos_Controller_U.position[1]=0;
	Pos_Controller_U.position[2]=0;
	Pos_Controller_U.yaw=+PI/2;

	ros::Subscriber positionSubscriber = nh.subscribe("/pose_estimation",1,pose_callback);
	ros::Subscriber consigneSubscriber = nh.subscribe("/position_target",1,target_callback);
	ros::Subscriber trajectoryConsgneSubscriber = nh.subscribe("/trajectory_plan",1,trajectory_plan_callback);
	twistPublisher = nh.advertise<geometry_msgs::Twist>("/cmd_vel",1);
	epsPublisher = nh.advertise<geometry_msgs::Pose>("eps",1);
#ifdef DEBUG_POS_CONTROLLER_OUTPUTS
	vis_pub = nh.advertise<visualization_msgs::Marker>( "visualization_marker", 0 );
	odomSpeedPublisher = nh.advertise<nav_msgs::Odometry>("/absolute_speed_command",1);
#endif

	ros::ServiceServer enable_service = nh.advertiseService("enable",setEnabled);
	ros::ServiceServer switch_rel_yaw = nh.advertiseService("enable_relative_yaw",setRelativeYaw);
	ros::ServiceServer state_server = nh.advertiseService("get_state",getState);

	if(!nh.getParam("distance_threshold",distance_threshold)){
		distance_threshold=DEFAULT_DISTANCE_THRESHOLD;
	}
		

	ros::Rate rate(5.0);
  while (ros::ok() && rtmGetErrorStatus(Pos_Controller_M) == (NULL)) {
		ros::spinOnce();
		step_PID();
		rate.sleep();
  }

  /* Terminate model */
  Pos_Controller_terminate();
  return 0;
}

