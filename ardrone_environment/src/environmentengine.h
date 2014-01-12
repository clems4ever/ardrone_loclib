#ifndef ENVIRONMENTENGINE_H
#define ENVIRONMENTENGINE_H

#include <QObject>
#include "ros_wrapper.h"

class Environment2D;
class MainWindow;

class EnvironmentEngine : public QObject
{
    Q_OBJECT
public:
    EnvironmentEngine(QObject *parent = 0);
    virtual ~EnvironmentEngine();

    void start();
    void quit();

    // Loads params from a xml configuration file
    void loadConfiguration(const QString& configFilename);

    const Environment2D& getEnvironment() const;


signals:
    void environmentImagePublished(IplImage *);
    void dronePositionUpdated();
    void tagListUpdated();

public slots:
    void addTag();

private:
    Environment2D *p_environment;
    ros_wrapper m_rosWrapper;
};

#endif // ENVIRONMENTENGINE_H
