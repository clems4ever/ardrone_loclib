cmake_minimum_required(VERSION 2.4.6)
include($ENV{ROS_ROOT}/core/rosbuild/rosbuild.cmake)


# Set the build type.  Options are:
#  Coverage       : w/ debug symbols, w/o optimization, w/ code-coverage
#  Debug          : w/ debug symbols, w/o optimization
#  Release        : w/o debug symbols, w/ optimization
#  RelWithDebInfo : w/ debug symbols, w/ optimization
#  MinSizeRel     : w/o debug symbols, w/ optimization, stripped binaries
#set(ROS_BUILD_TYPE RelWithDebInfo)

rosbuild_init()


#set the default path for built executables to the "bin" directory
#set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
#set the default path for built libraries to the "lib" directory
#set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

#uncomment if you have defined messages
rosbuild_genmsg()
#uncomment if you have defined services
rosbuild_gensrv()

# ARDroneEnvironment
FIND_PACKAGE(Qt4 REQUIRED)

#SET(ardrone_trajectory_DIR src/ardrone_trajectory)
SET(ardrone_trajectory_SOURCES src/main.cpp src/ardrone_trajectory.cpp src/ros_wrapper.cpp)
SET(ardrone_trajectory_HEADERS src/ardrone_trajectory.h src/ros_wrapper.h)

QT4_WRAP_CPP(ardrone_trajectory_HEADERS_MOC ${ardrone_trajectory_HEADERS})

INCLUDE(${QT_USE_FILE})
ADD_DEFINITIONS(${QT_DEFINITIONS})

rosbuild_add_executable(ardrone_trajectory ${ardrone_trajectory_SOURCES}
    ${ardrone_trajectory_HEADERS_MOC})
TARGET_LINK_LIBRARIES(ardrone_trajectory ${QT_LIBRARIES})

