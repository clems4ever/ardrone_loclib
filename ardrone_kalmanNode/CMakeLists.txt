cmake_minimum_required(VERSION 2.4.6)
include($ENV{ROS_ROOT}/core/rosbuild/rosbuild.cmake)
include_directories("Kalman_matlab/codegen/lib/Kalman_boucle")
include_directories("../ardrone_autonomy")
include_directories("../tum_ardrone")

# Set the build type.  Options are:
#  Coverage       : w/ debug symbols, w/o optimization, w/ code-coverage
#  Debug          : w/ debug symbols, w/o optimization
#  Release        : w/o debug symbols, w/ optimization
#  RelWithDebInfo : w/ debug symbols, w/ optimization
#  MinSizeRel     : w/o debug symbols, w/ optimization, stripped binaries
#set(ROS_BUILD_TYPE RelWithDebInfo)

rosbuild_init()

#set the default path for built executables to the "bin" directory
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
#set the default path for built libraries to the "lib" directory
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

#uncomment if you have defined messages
rosbuild_genmsg()
#uncomment if you have defined services
#rosbuild_gensrv()


#common commands for building c++ executables and libraries
rosbuild_add_library(${PROJECT_NAME} Kalman_matlab/codegen/lib/Kalman_boucle/Kalman_boucle.cpp)
#rosbuild_add_library(${PROJECT_NAME} K/example.cpp)
#target_link_libraries(${PROJECT_NAME} another_library)
#rosbuild_add_boost_directories()
#rosbuild_link_boost(${PROJECT_NAME} thread)
rosbuild_add_executable(kalmanNode src/kalmanNode.cpp
Kalman_matlab/codegen/lib/Kalman_boucle/Kalman_boucle.cpp 
Kalman_matlab/codegen/lib/Kalman_boucle/inv.cpp 
Kalman_matlab/codegen/lib/Kalman_boucle/rt_nonfinite.cpp
Kalman_matlab/codegen/lib/Kalman_boucle/rtGetNaN.cpp
Kalman_matlab/codegen/lib/Kalman_boucle/rtGetInf.cpp
)
#target_link_libraries(example ${PROJECT_NAME})
