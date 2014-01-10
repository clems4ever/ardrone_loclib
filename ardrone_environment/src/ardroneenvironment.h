#ifndef ARDRONEENVIRONMENT_H
#define ARDRONEENVIRONMENT_H

#include <QObject>
#include <QImage>

class EnvironmentEngine;
class MainWindow;

class ARDroneEnvironment : public QObject
{
    Q_OBJECT
public:
    explicit ARDroneEnvironment(QObject *parent = 0);

    void start();
    
signals:
    
public slots:
    void cleanQuit();
    void refreshDronePosition();
    void refreshTagsTable();
    
private:
    EnvironmentEngine *p_environmentEngine;
    MainWindow *p_mainWindow;
};

#endif // ARDRONEENVIRONMENT_H
