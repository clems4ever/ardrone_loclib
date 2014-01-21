// Pour publier un TAG :
// rostopic pub tag_position geometry_msgs/Point '{x: 20000, y: 40000, z: 0}'

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
#include "rt_nonfinite.h"
#include "inv.h" 
#include "Kalman_boucle.h"
#include <sstream>
 #include <math.h>
// %EndTag(ROS_HEADER)%
// %Tag(MSG_HEADER)%
#include "std_msgs/String.h"
#include "geometry_msgs/Point.h"
#include "geometry_msgs/Pose.h"
#include "geometry_msgs/Vector3.h"
#include "sensor_msgs/Imu.h"
#include "nav_msgs/Odometry.h"
#include <ardrone_autonomy/Navdata.h>
#include "tum_ardrone/filter_state.h"
// %EndTag(MSG_HEADER)%

// Variables d'acquisition
double x_tum =0.0;
double y_tum =0.0;
double z_tum =0.0;
double x_imu=0.0;
double y_imu= 0.0;
double x_gps=0.0;
double y_gps=0.0;

//Initialisation du tag avec une valeur GPS
double x_tag=0.0;
double y_tag=0.0;
double x_odom=0.0;
double y_odom=0.0;

// Variables de KALMAN
// Déclaration des variables du filtre.  
// Covariance R  
// Incertitudes = Variance = EcartType²
    double ErreurGPS = 20; 
    double ErreurTAG = 0.01;
    double ErreurODOM = 5;
    double ErreurTUM = 2;
    double Rgps = ErreurGPS*ErreurGPS;
    double Rodom = ErreurODOM*ErreurODOM;
    double Rtag = ErreurTAG*ErreurTAG;
    double Rtum = ErreurTUM*ErreurTUM;
    double R[64]={     Rgps,     0,       0,       0,       0,       0,       0,       0, 
                       0,        Rgps,    0,       0,       0,       0,       0,       0,
                       0,        0,       Rodom,   0,       0,       0,       0,       0,
                       0,        0,       0,       Rodom,   0,       0,       0,       0,
                       0,        0,       0,       0,       Rtag,    0,       0,       0,
                       0,        0,       0,       0,       0,       Rtag,    0,       0,
                       0,        0,       0,       0,       0,       0,       Rtum,    0,
                       0,        0,       0,       0,       0,       0,       0,       Rtum};




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

//Variables position TUM
double prevXtum = 0;
double prevYtum = 0;
double timeStamp = 0;

//Fraicheur des données
bool Ftag=false;
bool Ftum = false;
bool Fodom = false;
bool Fgps = false;

//Offset GPS
double offsetX=0;
double offsetY=0;
double timeTAG=0;
bool stateOffset=false;

//Changement de repères
double Xrst=0.0;
double Yrst=0.0;
double teta=0;
double yaw_current=0;

// Procédures qui s'executent à la réception d'un message subscribe
void messageCallbackTUM(const tum_ardrone::filter_state::ConstPtr &msg)
{
    //ROS_INFO("TUM -> x_tum: %f, y_tum: %f",msg->x, msg->y);
    
    /*
    // cas du reset
    if ( (msg->x > -0.001) && (msg->x < 0.001) && (msg->y > -0.001) && (msg->y < 0.001) )
    {
        x_tum = msg->x + x_tag;
        y_tum = msg->y + y_tag;
        
        prevXtum=0;
        prevYtum=0; 
    }
    else
    {    
        // récupération data + Changement de référentiel     
        x_tum = msg->x - prevXtum + x_tag;
        y_tum = msg->y - prevYtum + y_tag;

        prevXtum=x_tum - x_tag;
        prevYtum=y_tum - y_tag;    
    }
    */

    x_tum = msg->x + x_tag;
    y_tum = msg->y + y_tag;
    z_tum = msg->z;

    //Changement de repères
    x_imu = Xrst + x_tum*cos(teta)-y_tum*sin(teta);
    y_imu = Yrst + y_tum*cos(teta)+x_tum*sin(teta);

    // Variable prête
    Ftum=true;        
    
    //ROS_INFO("RTUM/ ATUM -> x_Rtum: %f, y_Rtum: %f / x_Atum: %f, y_Atum: %f",x_tum, y_tum, x_imu, y_imu);
}

void messageCallbackYAW(const tum_ardrone::filter_state::ConstPtr &msg)
{
  yaw_current=msg->yaw;
  //ROS_INFO("ANGLE -> yaw: %f, theta: %f ", yaw_current, teta);
}

void messageCallbackGPS(const nav_msgs::Odometry::ConstPtr &msg)
{
    // Récupération data
    x_gps=msg->pose.pose.position.x;
    y_gps=msg->pose.pose.position.y;

    // /!\ A tester : Correction du drift du GPS à partir des TAGS
    /*
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
    
    */

    // Variable prête
    Fgps=true;
    //ROS_INFO("GPS -> x_gps: %f, y_gps: %f",x_gps, y_gps);
}


 void messageCallbackODOM(const nav_msgs::Odometry::ConstPtr &msg)
{
    // Récupération data
    x_odom=msg->pose.pose.position.x;
    y_odom=msg->pose.pose.position.y;

    // Variable prête
    Fodom=true;
    //ROS_INFO("ODOM -> x_odom: %f, y_odom: %f", x_odom, y_odom);
}

 void messageCallbackTAG(const geometry_msgs::Point::ConstPtr &msg)
{
    // Récupération data
    x_tag=msg->x;
    y_tag=msg->y;

    // Variable prête
    Ftag=true;
    //ROS_INFO("TAG -> x_tag: %f, y_tag: %f", x_tag, y_tag);

    //Acquisition du temps pour le calcul de l'offset du GPS
    timeTAG=ros::Time::now().toSec();
    stateOffset=true;
}

// Verifie la fraicheur de la données
// Si nouvelle data, renvoie la de la covariance
// Si non, renvoie une covariance élevée pour ne pas prendre la mesure en compte dans le Kalman
// t = true -> nouvelle data 
//   = false -> pas de nouvelle data
// v = valeur de la covariance si nouvelle data
// matrix_zone = position de la covariance dans la matrice R
// type = gps || odom || tag || tum
// \return la valeur de la covariance correcte en fonction de l'arriver des data et met à jour la covariance associée 
double checkData(bool t, double v, int matrix_zone, int type)
{    
    double val=0;
    // Si variable non fraiche
    if(t==false)
    {
      R_point[matrix_zone]=1000000000;
      
      /* Même avec une covariance élevée, on a un doute de l'impact de la mesure, on l'initialise à une valeur proche
      // Si coordonnée sur x
      if(matrix_zone == 0 || matrix_zone == 18 || matrix_zone == 36 || matrix_zone == 54)
      {ROS_INFO("ANGLE -> yaw: %f, theta: %f ", yaw_current, teta);
            val = Prediction_point[0];
      }
      
      // Si coordonnée sur x
      if(matrix_zone == 9 || matrix_zone == 27 || matrix_zone == 45 || matrix_zone == 63)
      {
            val = Prediction_point[1];
      }    
      */
      val=v;
    }
    // Sinon ...
    else 
    {
      val=v;
      if(type==1)
        R_point[matrix_zone]=Rgps;
      if(type==2)
        R_point[matrix_zone]=Rodom;
      if(type==3)
        R_point[matrix_zone]=Rtag;
      if(type==4)
        R_point[matrix_zone]=Rtum;
    }

    return val;  
}



/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////// MAIN ////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char **argv)
{

  ros::init(argc, argv, "kalmanNode");

  ros::NodeHandle n;
  timeStamp=ros::Time::now().toSec();

  //Publisher
  ros::Publisher KalmanPos_pub = n.advertise<geometry_msgs::Point>("kalman_position", 10);
  //ros::Publisher KalmanPos_pub = n.advertise<geometry_msgs::Pose>("kalman_position", 10);
  
  ros::Publisher reset_tum_pub = n.advertise<std_msgs::String>("tum_ardrone/com",50);
    
  // message de reset de TUM
  std_msgs::String rst;
  std::stringstream ss;
  ss << "f reset" ;
  rst.data = ss.str();
  
  // Déclaration du message qui servira à publier la position estimée du kalman
  geometry_msgs::Point positionMsg;
  //geometry_msgs::Pose positionMsg;

  //Subscriber
  ros::Subscriber TUM_sub = n.subscribe("/ardrone/predictedPose", 1000, messageCallbackTUM);
  ros::Subscriber YAW_sub = n.subscribe("/ardrone/predictedPose", 1000, messageCallbackYAW);
  ros::Subscriber ODOM_sub = n.subscribe("/odom", 1000,messageCallbackODOM );
  ros::Subscriber GPS_sub = n.subscribe("/gps_odom", 1000,messageCallbackGPS);
  ros::Subscriber TAG_sub = n.subscribe("/tag_position", 1000, messageCallbackTAG);


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
        
        //  Afin de reinitialiser la position donnée par TUM
        if (Ftag==true)
        {
            //CHANGEMENTS ICI POUR LE REPERE
            Xrst=x_tag;
            Yrst=y_tag;
            teta=yaw_current;

            //FIN DES CHANGEMENTS

            reset_tum_pub.publish(rst);
        }
        
        Z[6]=checkData(Ftum,x_imu, 54,4);
        Z[7]=checkData(Ftum,y_imu, 63,4);

        //Fonction Kalman Boucle 
        //ROS_INFO("TUM -> x_tum: %f, y_tum: %f",x_tum, y_tum);
        //ROS_INFO("TUM -> x_tum: %f, y_tum: %f",Zprec_point[6], Zprec_point[7]);
        //ROS_INFO("IMU -> x_imu: %f, y_imu: %f",x_imu, y_imu);
        
        ROS_INFO("RTUM -> x_Rtum: %f, y_Rtum: %f ",x_tum, y_tum);       
        ROS_INFO("ATUM -> x_Atum: %f, y_Atum: %f ",x_imu, y_imu);
        ROS_INFO("TUM -> x_tum: %f, y_tum: %f ",Zprec_point[6], Zprec_point[7]);
        ROS_INFO("GPS -> x_gps: %f, y_gps: %f ",Zprec_point[0], Zprec_point[1]);
        ROS_INFO("ODOM -> x_odom: %f, y_odom: %f ",Zprec_point[2], Zprec_point[3]);
        ROS_INFO("TAG -> x_tag: %f, y_tag: %f ",Zprec_point[4], Zprec_point[5]);
        ROS_INFO("ANGLE -> yaw: %f, theta: %f ", yaw_current, teta);
        ROS_INFO("COVARIANCE R -> RGPS: %f, RODOM: %f, RTAG: %f, RxTUM: %f, RyTUM: %f",R_point_precedent[0],R_point_precedent[18],R_point_precedent[36],R_point_precedent[54],R_point_precedent[63]);
        
        Kalman_boucle(R_point_precedent, Xprec_point,Pprec_point,Zprec_point, Xk_point, Pk_point , Prediction_point);

        //Variables non fraiches
        Ftag=false;
        Fodom=false;
        Ftum=false;
        Fgps=false;        
        

        //Mise a jour des variables
        Zprec_point=Z;  
        R_point_precedent=R_point;
        Xprec_point=Xk_point;
        Pprec_point=Pk_point;
        
        //Publication de la position issue du Kalman
        // message type Point
        positionMsg.x = Prediction_point[0];
        positionMsg.y = Prediction_point[1];
        positionMsg.z = z_tum;
        
        /* message type Pose
        positionMsg.position.x = Prediction_point[0];
        positionMsg.position.y = Prediction_point[1];
        positionMsg.position.z = z_tum;
        positionMsg.orientation.x = 0;  // useless
        positionMsg.orientation.y = 0;  // useless
        positionMsg.orientation.z = 0;  // Orientation absolue du drone
        positionMsg.orientation.w = 0;  // useless
        */

        KalmanPos_pub.publish(positionMsg);
        
        

        ros::spinOnce();

        loop_rate.sleep();
        ++count;

   };

  return 0;
}

