#ifndef ENVIRONMENTENGINE_H
#define ENVIRONMENTENGINE_H

#include <QObject>
#include "ros_wrapper.h"

class Map2D;

class EnvironmentEngine : public QObject
{
    Q_OBJECT
public:
    EnvironmentEngine(QObject *parent = 0);
    virtual ~EnvironmentEngine();

    void start();


signals:

public slots:
    void cleanup();

private:
    Map2D *p_map;
    ros_wrapper m_rosWrapper;

};

#endif // ENVIRONMENTENGINE_H
