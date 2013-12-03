#-------------------------------------------------
#
# Project created by QtCreator 2013-11-22T23:45:52
#
#-------------------------------------------------

QT       += core gui widgets

TARGET = ardrone_environment
#CONFIG   += console
#CONFIG   -= app_bundle

INCLUDEPATH = ../../srv_gen/cpp/include/ \
                /opt/ros/fuerte/include/


TEMPLATE = app


SOURCES += \
    main.cpp \
    environmentengine.cpp \
    map2d.cpp \
    ros_wrapper.cpp


HEADERS += \
    environmentengine.h \
    map2d.h \
    ros_wrapper.h
