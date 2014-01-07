#include "ardroneenvironment.h"

#include <QApplication>

#include "environmentengine.h"
#include "mainwindow.h"

ARDroneEnvironment::ARDroneEnvironment(QObject *parent) :
    QObject(parent)
{

    p_environmentEngine = new EnvironmentEngine(this);
    p_mainWindow = new MainWindow();

    p_mainWindow->fillTagsTable(p_environmentEngine->getEnvironment().getTagsList());

    connect(p_environmentEngine, SIGNAL(environmentImagePublished(IplImage*)), p_mainWindow, SLOT(refreshEnvironmentImage(IplImage*)) );


    // The app is closed with the quit action in the menubar
    connect(p_mainWindow, SIGNAL(quitAsked()), this, SLOT(cleanQuit()));

    // The window has been closed with the window close event
    connect(p_mainWindow, SIGNAL(closing()), this, SLOT(cleanQuit()));
}

/**
 *
 */
void ARDroneEnvironment::start()
{
    p_environmentEngine->start();
    p_mainWindow->show();
}

/**
  *
  */
void ARDroneEnvironment::cleanQuit()
{
    p_environmentEngine->quit();
    p_mainWindow->close();

    qApp->quit();
}
