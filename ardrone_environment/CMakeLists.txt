cmake_minimum_required(VERSION 2.4.6)
include($ENV{ROS_ROOT}/core/rosbuild/rosbuild.cmake)

# Set the build type.  Options are:
#  Coverage       : w/ debug symbols, w/o optimization, w/ code-coverage
#  Debug          : w/ debug symbols, w/o optimization
#  Release        : w/o debug symbols, w/ optimization
#  RelWithDebInfo : w/ debug symbols, w/ optimization
#  MinSizeRel     : w/o debug symbols, w/ optimization, stripped binaries
set(ROS_BUILD_TYPE RelWithDebInfo)

rosbuild_init()

#set the default path for built executables to the "bin" directory
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
#set the default path for built libraries to the "lib" directory
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

#uncomment if you have defined messages
rosbuild_genmsg()
#uncomment if you have defined services
rosbuild_gensrv()

# ARDroneEnvironment
FIND_PACKAGE(Qt4 REQUIRED)

include_directories("srv_gen/cpp/include")
#SET(ardrone_environment_DIR src/ardrone_environment)
SET(ardrone_environment_SOURCES src/main.cpp src/environmentengine.cpp src/map2d.cpp src/ros_wrapper.cpp)
SET(ardrone_environment_HEADERS src/environmentengine.h src/map2d.h src/ros_wrapper.h)

QT4_WRAP_CPP(ardrone_environment_HEADERS_MOC ${ardrone_environment_HEADERS})

INCLUDE(${QT_USE_FILE})
ADD_DEFINITIONS(${QT_DEFINITIONS})

rosbuild_add_executable(ardrone_environment ${ardrone_environment_SOURCES}
    ${ardrone_environment_HEADERS_MOC})
TARGET_LINK_LIBRARIES(ardrone_environment ${QT_LIBRARIES})

#common commands for building c++ executables and libraries
#rosbuild_add_library(${PROJECT_NAME} src/example.cpp)
#target_link_libraries(${PROJECT_NAME} another_library)
#rosbuild_add_boost_directories()
#rosbuild_link_boost(${PROJECT_NAME} thread)
#rosbuild_add_executable(example examples/example.cpp)
#rosbuild_add_executable(odom_to_path src/rviz_tools/odom_to_path.cpp)
#target_link_libraries(example ${PROJECT_NAME})
