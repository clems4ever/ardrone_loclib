#!/bin/bash

cd Kalman_matlab/codegen/lib/Kalman_boucle/
./compiling.sh
cd
cd fuerte_workspace/ardrone_kalmanNode/
rosmake
rosrun ardrone_kalmanNode kalmanNode
