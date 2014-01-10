#include "environmentengine.h"

#include "environment2d.h"

#include <QImageReader>
#include <QCoreApplication>
#include <QFile>
#include <QDomDocument>

EnvironmentEngine::EnvironmentEngine(QObject *parent) :
    QObject(parent), m_rosWrapper(this)
{
    p_environment = new Environment2D("insa_background", "insa_wallmask.bmp", "insa_tagsmask.bmp");

    m_rosWrapper.storeEnvironment2D(p_environment);

    connect(&m_rosWrapper, SIGNAL(environmentImagePublished(IplImage*)), this, SIGNAL(environmentImagePublished(IplImage*)));
    connect(p_environment, SIGNAL(dronePositionUpdated()), this, SIGNAL(dronePositionUpdated()));
}

EnvironmentEngine::~EnvironmentEngine()
{
}

/** @brief Starts the ros wrapper thread.
  *
  */
void EnvironmentEngine::start()
{
    m_rosWrapper.start();
}

/** @brief Quits the engine by shutting down the ros thread.
  *
  */
void EnvironmentEngine::quit()
{
    // shutdowns ros
    m_rosWrapper.end();
    // Wait for the thread to finish
    while(!m_rosWrapper.isFinished());
}

/** @brief Loads a configuration from a .conf file (XML) where all parameters will be stored.
  *
  */
void EnvironmentEngine::loadConfiguration(const QString &configFilename)
{
    QFile configFile(configFilename);
    QDomDocument document;
    document.setContent(&configFile);
}

/** @brief Returns a reference to the environment
  */
const Environment2D& EnvironmentEngine::getEnvironment() const
{
    return *p_environment;
}

void EnvironmentEngine::addTag()
{
    Environment2D::Tag t;
    t.id = -1;
    t.x = -1;
    t.y = -1;
    p_environment->appendTag(t);
    emit tagListUpdated();
}
