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
#rosbuild_gensrv()

# ARDroneEnvironment
FIND_PACKAGE(Qt4 REQUIRED)
SET(QT_USE_QTXML TRUE)
#find_package(Qt5Xml)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

#include_directories("srv_gen/cpp/include")
#include_directories("msg_gen/cpp/include")
#SET(ardrone_moves_gui_DIR src/ardrone_moves_gui)
SET(ardrone_moves_gui_SOURCES src/main.cpp src/mainwindow.cpp)
SET(ardrone_moves_gui_HEADERS src/mainwindow.h)

QT4_WRAP_CPP(ardrone_moves_gui_HEADERS_MOC ${ardrone_moves_gui_HEADERS})
QT4_WRAP_UI(ardrone_moves_gui_UIS_HDRS
	src/mainwindow.ui
	)

INCLUDE(${QT_USE_FILE})
ADD_DEFINITIONS(${QT_DEFINITIONS})

rosbuild_add_executable(ardrone_moves_gui ${ardrone_moves_gui_SOURCES}
    ${ardrone_moves_gui_HEADERS_MOC} ${ardrone_moves_gui_UIS_HDRS})
TARGET_LINK_LIBRARIES(ardrone_moves_gui ${QT_LIBRARIES})

