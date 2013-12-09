#include "environmentengine.h"

#include "map2d.h"

#include <QImageReader>

EnvironmentEngine::EnvironmentEngine(QObject *parent) :
    QObject(parent)
{
    p_map = new Map2D();
    p_map->load(QString("images/insa.jpg"), QString("images/insa_buildings.bmp"));
}

void EnvironmentEngine::start()
{

}
