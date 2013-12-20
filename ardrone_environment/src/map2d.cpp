
#include "map2d.h"

#include <QUrl>
#include <QImage>
#include <QString>
#include <QSize>
#include <QRgb>
#include <QDebug>
#include <QColor>

#include "opencv/cv.h"

Map2D::Map2D(QObject * parent) :
    QObject(parent)
{
    p_tilesArray = 0;
}

Map2D::~Map2D()
{
    if(p_tilesArray == 0)
        return;

    for(int i=0; i<m_size.width(); i++)
    {
        delete[] p_tilesArray[i];
    }
    delete[] p_tilesArray;
}

void Map2D::load(const QString &backgroundLayer, const QString &environmentLayer)
{
    int currentId = 0;

    if(!m_maskImage.load(environmentLayer))
    {
        qDebug("Map2D: Environment image not loaded");
        throw std::exception();
    }

    if(!m_backgroundImage.load(backgroundLayer))
    {
        qDebug("Map2D: Background image not loaded");
        throw std::exception();
    }

    if(m_maskImage.size() != m_backgroundImage.size())
    {
        qDebug("Two layers with different size");
        throw std::exception();
    }

    m_environmentImage = m_backgroundImage.copy();

    p_tilesArray = new Tile*[m_backgroundImage.size().width()];
    for(int i=0; i<m_backgroundImage.width(); i++)
    {
        p_tilesArray[i] = new Tile[m_backgroundImage.size().height()];
        for(int j=0; j<m_backgroundImage.size().height(); j++)
        {
            //printf("%x\n", m_environmentImage.pixel(i, j));
            if((m_maskImage.pixel(i, j) & 0x00FFFFFF) == 0){
                p_tilesArray[i][j].type = WALL;
            }else if((m_maskImage.pixel(i, j) & 0x00FFFFFF) == 0x00FF00){
                p_tilesArray[i][j].type = TAG;
                p_tilesArray[i][j].id = currentId;
                TagPosition tagPosition;
                tagPosition.x = i;
                tagPosition.y = j;
                m_tagPositionList.append(tagPosition);
                currentId++;
            }else{
                p_tilesArray[i][j].type = EMPTY;
            }
        }
    }
}

QSize Map2D::getSize() const
{
    return m_backgroundImage.size();
}

const QImage &Map2D::getBackground() const
{
    return m_backgroundImage;
}

void Map2D::toggleWall(const QPoint &p)
{
    p_tilesArray[p.x()][p.y()].type = (p_tilesArray[p.x()][p.y()].type == WALL)? EMPTY : WALL;
}


Map2D::Tile Map2D::getTile(int x, int y) const
{
    return p_tilesArray[x][y];
}

void Map2D::computeEnvironmentImage()
{
}

QList<Map2D::TagPosition> Map2D::getTagPositions() const
{
    return m_tagPositionList;
}

int Map2D::getTagId(int x, int y) const
{
    if(p_tilesArray[x][y].type != TAG)
        throw std::exception();
    return p_tilesArray[x][y].id;
}

QVariant Map2D::getTagValue(int x, int y) const
{
    if(p_tilesArray[x][y].type != TAG)
        throw std::exception();
    return p_tilesArray[x][y].id;
}

IplImage* Map2D::qImage2IplImage(const QImage &qImage)
{
    QImage qimg = qImage.copy();
    IplImage *imgHeader = cvCreateImageHeader( cvSize(qimg.width(), qimg.height()), IPL_DEPTH_8U, 4);
    imgHeader->imageData = (char*) qimg.bits();

    uchar* newdata = (uchar*) malloc(sizeof(uchar) * qimg.byteCount());
    memcpy(newdata, qimg.bits(), qimg.byteCount());
    imgHeader->imageData = (char*) newdata;
    return imgHeader;
}

IplImage* Map2D::getCvImage()
{
    return Map2D::qImage2IplImage(m_environmentImage);
}
