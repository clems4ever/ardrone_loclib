ardrone_kalmanNode
==============

Node including a Kalman filter. Run with the launchfile. The launchfile run **roscore**, **ardrone_autonomy** and **tum_ardrone**

### Others packages needed

This node use data provide by differents sensors and packages :

**imu data** estimated by **tum_ardrone** using drone_stateestimation
          
**gps_data** provide by another node in the lib
        
**tag_data** provide by tag_detection
        
        
That's why it is needed to run the three nodes

### Installation

In order to install the node, just execute these command lines :
```
roscd
cd ardrone_kalmanNode
cmake .
rosmake

```

### Execution

Simply execute the launchfile in this order

```
roscd 
cd ardrone_kalmanNode/launch
roslaunch driver_tum.launch
roslaunch kalman_node.launch

```

The first launch run **tum_ardrone** and **ardrone_autonomy**.
 
The second run **ardrone_kalmanNode**

### Topics and data

The node publish the predicted position in ```geometry_msgs::Point``` on ```kalman_position``` topic.

The node send reset order to **tum_ardrone** by publishing ```std_msgs::String``` on ```tum_ardrone/com```.

The node subscribe to several topics for data acquisition : 

   * To get the tag position it receive ```geometry_msgs::Point``` on  ```tag_position```
   * To get the gps position it receive ```nav_msgs::Odometry``` on  ```gps_odom```
   * To get the tum position estimation, it receive ```tum_ardrone::filter_state``` on  ```ardrone/predictedPose```
   * To get the yaw orientation estimation, it receive ```tum_ardrone::filter_state``` on  ```ardrone/predictedPose```
   
### Functionnement

The node get all the values with a rate loop. It handle the data missing. Each loops, it compute a prediction using Kalman Algorithm in absolute coordinates. 

If a QRCode appear, it reset tum and get the yaw angle. Thanks to this angle, it compute a vector rotation, allowing a coherent set of absolute coordinates.

### Ways of improvement
Improve the data management. If a data is missing, kalman filter has to not consider it.

Improve vector rotation algorithm.

Improve Kalman filter and reactivity.
