ardrone_kalmanNode
==============

Node including a Kalman filter. Run with the launchfile. The launchfile run **roscore**, **ardrone_autonomy** and **tum_ardrone**

### Others packages needed

This node use data provide by differents sensors and packages :
        >**imu data** estimated by **tum_ardrone** using drone_stateestimation 
        >**gps_data** provide by another node in the lib
        >**tag_data** provide by tag_detection.
        
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
