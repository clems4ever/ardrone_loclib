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
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
#set the default path for built libraries to the "lib" directory
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

#uncomment if you have defined messages
#rosbuild_genmsg()
#uncomment if you have defined services
rosbuild_gensrv()

# ARDroneEnvironment
#FIND_PACKAGE(Qt4 REQUIRED)
#
#SET(ardrone_environment_DIR src/ardrone_environment)
#SET(ardrone_environment_SOURCES main.cpp environmentengine.cpp map2d.cpp ros_wrapper.cpp)
#SET(ardrone_environment_s prepend_path( ardrone_environment_SOURCES ${ardrone_environment_DIR} ))
#SET(ardrone_environment_HEADERS environmentengine.h map2d.h ros_wrapper.h)
#SET(ardrone_environment_h prepend_path(ardrone_environment_HEADERS ${ardrone_environment_DIR} ))
#
#QT4_WRAP_CPP(ardrone_environment_HEADERS_MOC ${ardrone_environment_h})
#
#INCLUDE(${QT_USE_FILE})
#ADD_DEFINITIONS(${QT_DEFINITIONS})
#
#ADD_EXECUTABLE(ardrone_environment ${ardrone_environment_s} 
#    ${ardrone_environment_HEADERS_MOC})
#TARGET_LINK_LIBRARIES(ardrone_environment ${QT_LIBRARIES})

set(controller_dir ${PROJECT_SOURCE_DIR}/src/Pos_Controller)
set(controller_sources ${controller_dir}/Pos_Controller.cpp ${controller_dir}/Pos_Controller_data.cpp ${controller_dir}/rtGetInf.cpp ${controller_dir}/rtGetNaN.cpp ${controller_dir}/rt_mod_snf.cpp ${controller_dir}/rt_mod.cpp ${controller_dir}/rt_nonfinite.cpp)

#common commands for building c++ executables and libraries
#rosbuild_add_library(${PROJECT_NAME} src/example.cpp)
#rosbuild_add_boost_directories()
#rosbuild_link_boost(${PROJECT_NAME} thread)
#rosbuild_add_executable(example examples/example.cpp)
#include_directories(${PROJECT_SOURCE_DIR}/speed_controller)
#include_directories(${PROJECT_SOURCE_DIR})
#target_link_libraries(${PROJECT_NAME} another_library)
rosbuild_add_library(Pos_Controller ${controller_sources})
include_directories(${controller_dir})
rosbuild_add_executable(position_controller src/position_controller.cpp)
rosbuild_add_executable(position_controller_tf src/position_controller_tf.cpp)
target_link_libraries(position_controller Pos_Controller)
target_link_libraries(position_controller_tf Pos_Controller)
#rosbuild_add_executable(altd_control src/altd_control.cpp src/pid.cpp)
#rosbuild_add_executable(odom_to_path src/rviz_tools/odom_to_path.cpp)
#target_link_libraries(example ${PROJECT_NAME})

