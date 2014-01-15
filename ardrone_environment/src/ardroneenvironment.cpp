#include "ardroneenvironment.h"

#include <QApplication>
#include <QFileDialog>

#include "environmentengine.h"
#include "mainwindow.h"

ARDroneEnvironment::ARDroneEnvironment(QObject *parent) :
    QObject(parent)
{

    p_environmentEngine = new EnvironmentEngine(this);
    //p_environmentEngine->loadConfiguration("insa_background", "insa_wallmask.bmp", "insa_tagsmask.bmp");
    p_mainWindow = new MainWindow();

    p_mainWindow->refreshTagsTable(p_environmentEngine->getTagsList());


    // The app is closed with the quit action in the menubar
    connect(p_mainWindow, SIGNAL(quitAsked()), this, SLOT(cleanQuit()));

    connect(p_mainWindow, SIGNAL(openConfigurationAsked()), this, SLOT(loadConfiguration()));
    connect(p_mainWindow, SIGNAL(saveConfigurationAsked()), this, SLOT(saveConfiguration()));

    // The window has been closed with the window close event
    connect(p_mainWindow, SIGNAL(closing()), this, SLOT(cleanQuit()));


    // Refreshes tag table
    connect(p_mainWindow, SIGNAL(addTagAsked()), p_environmentEngine, SLOT(addTag()));
    connect(p_environmentEngine, SIGNAL(tagListUpdated()), this, SLOT(refreshTagsTable()));

    connect(p_mainWindow, SIGNAL(offsetXChanged(double)), p_environmentEngine, SLOT(setOffsetX(double)));
    connect(p_mainWindow, SIGNAL(offsetYChanged(double)), p_environmentEngine, SLOT(setOffsetY(double)));
    connect(p_mainWindow, SIGNAL(scaleXChanged(double)), p_environmentEngine, SLOT(setScaleX(double)));
    connect(p_mainWindow, SIGNAL(scaleYChanged(double)), p_environmentEngine, SLOT(setScaleY(double)));

    connect(p_environmentEngine, SIGNAL(environmentImagePublished(IplImage*)), p_mainWindow, SLOT(refreshEnvironmentImage(IplImage*)) );
    connect(p_environmentEngine, SIGNAL(dronePositionUpdated()), this, SLOT(refreshDronePosition()));

    connect(p_mainWindow, SIGNAL(tagChanged(int,QString,QString,double,double)), p_environmentEngine, SLOT(updateTag(int,QString,QString,double,double)));
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
    /*p_environmentEngine->quit();
    p_mainWindow->close();*/

    qApp->quit();
}


void ARDroneEnvironment::refreshDronePosition()
{
    p_mainWindow->refreshDronePosition(p_environmentEngine->getDronePosition());
}

void ARDroneEnvironment::refreshTagsTable()
{
    p_mainWindow->refreshTagsTable(p_environmentEngine->getTagsList());
}

/** @brief slot that saves a configuration from a file
  */
void ARDroneEnvironment::saveConfiguration()
{
    QString filename = QFileDialog::getSaveFileName(p_mainWindow, "Save file", "", "*.arenv");
    if(filename.isEmpty()) return;
    filename = (filename.endsWith(".arenv")) ? filename : filename + ".arenv";
    p_environmentEngine->saveConfiguration(filename);
}


/** @brief slot that loads a configuration from a file
  */
void ARDroneEnvironment::loadConfiguration()
{
    QString filename = QFileDialog::getOpenFileName(p_mainWindow, "Open file", "", "*.arenv");
    if(filename.isEmpty()) return;
    p_environmentEngine->loadConfiguration(filename);
    p_mainWindow->refreshOffsetAndScale(p_environmentEngine->getOffset(), p_environmentEngine->getScale());
    p_mainWindow->refreshTagsTable(p_environmentEngine->getTagsList());
}

