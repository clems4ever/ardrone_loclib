#include "environmentengine.h"

#include "map2d.h"

#include <QImageReader>
#include <QCoreApplication>

EnvironmentEngine::EnvironmentEngine(QObject *parent) :
    QObject(parent), m_rosWrapper(this)
{
    p_map = new Map2D();
    p_map->load(QString("images/insa.jpg"), QString("images/insa_buildings.bmp"));
    m_rosWrapper.storeMap2D(p_map);
}

EnvironmentEngine::~EnvironmentEngine()
{
    m_rosWrapper.exit();
}

void EnvironmentEngine::start()
{
    m_rosWrapper.start();
}

void EnvironmentEngine::cleanup()
{
}
