#-------------------------------------------------
#
# Project created by QtCreator 2013-11-22T23:45:52
#
#-------------------------------------------------

QT += core gui xml

TARGET = ardrone_environment
#CONFIG   += console
#CONFIG   -= app_bundle

INCLUDEPATH =   ../srv_gen/cpp/include/ \
                ../msg_gen/cpp/include/ \
                /opt/ros/fuerte/include/


TEMPLATE = app


SOURCES += \
    main.cpp \
    environmentengine.cpp \
    ros_wrapper.cpp \
    ardroneenvironment.cpp \
    mainwindow.cpp \
    mapviewer.cpp


HEADERS += \
    environmentengine.h \
    ros_wrapper.h \
    ardroneenvironment.h \
    mainwindow.h \
    cvimageviewer.h \
    mapviewer.h
