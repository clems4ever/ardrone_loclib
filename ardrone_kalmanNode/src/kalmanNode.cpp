/*
 * Copyright (C) 2008, Morgan Quigley and Willow Garage, Inc.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *   * Redistributions of source code must retain the above copyright notice,
 *     this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *   * Neither the names of Stanford University or Willow Garage, Inc. nor the names of its
 *     contributors may be used to endorse or promote products derived from
 *     this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */
// %Tag(FULLTEXT)%
// %Tag(ROS_HEADER)%
#include "ros/ros.h"
// %EndTag(ROS_HEADER)%
// %Tag(MSG_HEADER)%
#include "std_msgs/String.h"
#include "geometry_msgs/Point.h"
#include "sensor_msgs/Imu.h"
#include "geometry_msgs/Vector3.h"
#include "nav_msgs/Odometry.h"

#include "rt_nonfinite.h"
#include "inv.h" 
#include "Kalman_boucle.h"

#include <sstream>
#include <ardrone_autonomy/Navdata.h>
 #include "tum_ardrone/filter_state.h"

/**
 * This tutorial demonstrates simple sending of messages over the ROS system.
 */

// Variables d'acquisition
double x_imu =0.0;
double y_imu =0.0;

double x_gps=0.0;
double y_gps=0.0;


double x_tag=0.0;
double y_tag=0.0;

double x_odom=0.0;
double y_odom=0.0;

// Variables de KALMAN

// Déclaration des variables du filtre.  
// Covariance R  
// Dans un 1er temps on fixe les valeurs de la matrice des covariances
// Incertitudes = Variance = EcartType²
    int ErreurGPS = 20; 
    int ErreurTAG = 0.01;
    int ErreurODOM = 5;
    int ErreurA = 2;
    int ErreurV = ErreurA*ErreurA;
    double Rgps = ErreurGPS*ErreurGPS;
    double Rodom = ErreurODOM*ErreurODOM;
    double Rtag = ErreurTAG*ErreurTAG;
    double RVimu = ErreurV*ErreurV;
    double R[64]={     Rgps,     0,       0,       0,       0,       0,       0,       0, 
                       0,        Rgps,    0,       0,       0,       0,       0,       0,
                       0,        0,       Rodom,   0,       0,       0,       0,       0,
                       0,        0,       0,       Rodom,   0,       0,       0,       0,
                       0,        0,       0,       0,       Rtag,    0,       0,       0,
                       0,        0,       0,       0,       0,       Rtag,    0,       0,
                       0,        0,       0,       0,       0,       0,       RVimu,   0,
                       0,        0,       0,       0,       0,       0,       0,       RVimu};




//Etat précédents des variables dans kalman
double Xprec[4]={};
double Pprec[16]={};
double Zprec[8]={};

//Etat courants des variables de Kalman
double Z[8]={};
double Xk[4]={};
double Pk[16]={};
double Prediction[4]={};

//Pointeurs pour chaques variables de Kalman
double *R_point=R;
double *R_point_precedent=R;
double *Xprec_point=Xprec;
double *Pprec_point=Pprec;
double *Zprec_point=Zprec;
double *Z_point=Z;
double *Xk_point=Xk;
double *Pk_point=Pk;
double *Prediction_point=Prediction;

//Variables vitesse IMU
double prevXimu = 0;
double prevYimu = 0;
double timeStamp = 0;


//Correction du drift
int state=0;
int cpt=0;
double tabX[500]={};
double tabY[500]={};
double driftX=0;
double driftY=0;

//Fraicheur des données
bool Ftag=false;
bool Fimu = false;
bool Fodom = false;
bool Fgps = false;

//Offset GPS
double offsetX=0;
double offsetY=0;
double timeTAG=0;
bool stateOffset=false;



//void messageCallbackIMU(const sensor_msgs::Imu::ConstPtr &msg)
void messageCallbackIMU(const tum_ardrone::filter_state::ConstPtr &msg)
{

    x_imu=msg->x-prevXimu+x_tag;
    y_imu=msg->y-prevYimu+y_tag;

    //Changement de référenciel
    /*x_imu=msg->x+x_tag;
      y_imu=msg->y+y_tag;
    */


    prevXimu=x_imu;
    prevYimu=y_imu;

    Fimu=true;

        
}

void messageCallbackGPS(const nav_msgs::Odometry::ConstPtr &msg)
{

    x_gps=msg->pose.pose.position.x;
    y_gps=msg->pose.pose.position.y;

    if(stateOffset){
      if((ros::Time::now().toSec()-timeTAG)<5){
            offsetX=x_tag-x_gps;
            offsetY=y_tag-y_gps;
            stateOffset=false;
      }
      else
        stateOffset=false;
    }

    x_gps+=offsetX;
    y_gps+=offsetY;



    //Variable fraiche
    Fgps=true;
   
}


 void messageCallbackODOM(const nav_msgs::Odometry::ConstPtr &msg)
{
    x_odom=msg->pose.pose.position.x;
    y_odom=msg->pose.pose.position.y;

    //Variable fraiche
    Fodom=true;
    //ROS_INFO("ODOM -> x_odom: %f, y_odom: %f", msg->pose.pose.position.x, msg->pose.pose.position.y);
}

 void messageCallbackTAG(const geometry_msgs::Point::ConstPtr &msg)
{

    x_tag=msg->x;
    y_tag=msg->y;

    //Variable fraiche
    Ftag=true;

    //Acquisition du temps pour le calcul de l'offset du GPS
    timeTAG=ros::Time::now().toSec();
    stateOffset=true;

}

//Verifie la fraicheur de la données
//Si fraiche, renvoie la valeurd
//Si non, renvoie 2000000
double checkData(bool t, double v, int matrix_zone, int type){
    
    double val=0;

    if(t==false){
      R_point[matrix_zone]=4000;
      val=v;
    }

    else {
      val=v;
      if(type==1)
        R_point[matrix_zone]=Rgps;
      if(type==2)
        R_point[matrix_zone]=Rodom;
      if(type==3)
        R_point[matrix_zone]=Rtag;
      if(type==4)
        R_point[matrix_zone]=RVimu;
    }

    return val;
  
}

int main(int argc, char **argv)
{

  ROS_INFO("salu");

  ros::init(argc, argv, "kalmanNode");

  ros::NodeHandle n;
  timeStamp=ros::Time::now().toSec();

  //Publisher
  ros::Publisher KalmanPos_pub = n.advertise<geometry_msgs::Point>("Ardrone_KalmanPos", 10);
  
  // Déclaration du message qui servira à publier la position estimée du kalman
  geometry_msgs::Point positionMsg;

  //Subscriber
  ros::Subscriber IMU_sub = n.subscribe("/ardrone/predictedPose", 1000, messageCallbackIMU);
  ros::Subscriber ODOM_pub = n.subscribe("/odom", 1000,messageCallbackODOM );
  ros::Subscriber GPS_pub = n.subscribe("/gps", 1000,messageCallbackGPS);
  ros::Subscriber TAG_pub = n.subscribe("/qrcode", 1000, messageCallbackTAG);

  //loop rate
  ros::Rate loop_rate(1);


  int count = 0;
  while (ros::ok())
  {

    //Affectation vecteur de mesure
    Z[0]=checkData(Fgps,x_gps,0,1);
    Z[1]=checkData(Fgps,y_gps,9,1);
    Z[2]=checkData(Fodom,x_odom, 18,2);
    Z[3]=checkData(Fodom,x_odom, 27,2);
    Z[4]=checkData(Ftag,x_tag, 36,3);
    Z[5]=checkData(Ftag,y_tag, 45,3);
    Z[6]=checkData(Fimu,x_imu, 54,4);
    Z[7]=checkData(Fimu,y_imu, 63,4);

    //Fonction Kalman Boucle 
    Kalman_boucle(R_point_precedent, Xprec_point,Pprec_point,Zprec_point, Xk_point, Pk_point , Prediction_point);

    //Variables non fraiches
    Ftag=false;
    Fodom=false;
    Fimu=false;
    Fgps=false;        
    ROS_INFO("IMU -> x_imu: %f, y_imu: %f",x_imu, y_imu);

     //Mise a jour des variables
     Zprec_point=Z;  
     R_point_precedent=R_point;
     Xprec_point=Xk_point;
     Pprec_point=Pk_point;
    
    //Publication de la position issue du Kalman
    positionMsg.x = Prediction_point[0];
    positionMsg.y = Prediction_point[1];

    KalmanPos_pub.publish(positionMsg);

    ros::spinOnce();

    loop_rate.sleep();
    ++count;

   };

  return 0;
}

