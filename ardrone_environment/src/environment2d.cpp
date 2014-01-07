#include "environment2d.h"

#include <QPainter>

#include <exception>


Environment2D::Environment2D(const QString &backgroundFilename, const QString &wallMaskFilename, const QString &tagMaskFilename, QObject *parent)
{
    p_tilesArray = 0;
    QImage wallMaskImage(wallMaskFilename);
    QImage tagMaskImage(tagMaskFilename);
    m_dronePosition = QPoint(0,0);
    Tag tag;
    int currentTag = 0;


    m_backgroundImage.load(backgroundFilename);

    if(m_backgroundImage.size() != wallMaskImage.size())
    {
        throw std::exception();
    }

    if(m_backgroundImage.size() != tagMaskImage.size())
    {
        throw std::exception();
    }

    m_size = m_backgroundImage.size();

    p_tilesArray = new Tile*[m_backgroundImage.size().width()];

    // Initializes the array
    for(int i=0; i<m_size.width(); i++)
    {
        p_tilesArray[i] = new Tile[m_backgroundImage.size().height()];
        for(int j=0; j<m_size.height(); j++)
        {
            p_tilesArray[i][j] = EMPTY;
        }
    }

    // Loads the wall bricks
    for(int x=0; x<wallMaskImage.size().width(); x++)
    {
        for(int y=0; y<wallMaskImage.size().height(); y++)
        {
            if((wallMaskImage.pixel(x, y) & 0x00FFFFFF) == 0){
                p_tilesArray[x][y] = WALL;
            }
        }
    }


    // Loads the tags
    for(int x=0; x<tagMaskImage.size().width(); x++)
    {
        for(int y=0; y<tagMaskImage.size().height(); y++)
        {
            if((tagMaskImage.pixel(x, y) & 0x00FFFFFF) == 0)
            {
                tag.id = currentTag++;
                tag.value = "";
                tag.x = x;
                tag.y = y;
                m_tagList.append(tag);
            }
        }
    }
}


Environment2D::~Environment2D()
{
    if(p_tilesArray == 0)
        return;

    for(int i=0; i<m_size.width(); i++)
    {
        delete[] p_tilesArray[i];
    }
    delete[] p_tilesArray;
}

/** @brief Gets the tile at position x and y
  */
Environment2D::Tile Environment2D::getTile(int x, int y) const
{
    return p_tilesArray[x][y];
}


/** @brief Gets the environment size, i.e. width and height.
  */
QSize Environment2D::getSize() const
{
    return m_size;
}

void Environment2D::setMission(const Path &p)
{
    m_missionPath = p;
}


/** @brief Converts an image from QImage to an OpenCV format RGB888 with alpha
  */
IplImage* Environment2D::qImage2IplImage(const QImage &qImage)
{
    QImage qimg = qImage.copy();
    IplImage *imgHeader = cvCreateImageHeader( cvSize(qimg.width(), qimg.height()), IPL_DEPTH_8U, 4);
    imgHeader->imageData = (char*) qimg.bits();

    uchar* newdata = (uchar*) malloc(sizeof(uchar) * qimg.byteCount());
    memcpy(newdata, qimg.bits(), qimg.byteCount());
    imgHeader->imageData = (char*) newdata;
    return imgHeader;
}

IplImage* Environment2D::getCvImage()
{
    return Environment2D::qImage2IplImage(m_currentEnvironmentImage);
}


void Environment2D::computeImage()
{
    m_currentEnvironmentImage = QImage(m_size, QImage::Format_ARGB32);
    QPainter m_painter(&m_currentEnvironmentImage);

    m_painter.drawImage(0, 0, m_backgroundImage);

    float voffset = ((float)1.0);
    float hoffset = ((float)1.0);

    m_painter.setPen(Qt::black);

    int xmax = m_size.width();
    int ymax = m_size.height();

    m_painter.setPen(QColor(255, 0, 0, 100));

    // For all pixels on the map, draw the walls.
    for(int y=0; y<ymax; y++)
    {
        for(int x=0; x<xmax; x++)
        {
            if(p_tilesArray[x][y] == Environment2D::WALL)
            {
                m_painter.setPen(QColor(0, 0, 255, 100));
                m_painter.drawPoint(x*voffset, y*hoffset);
            }

            /*if(p_tilesArray[x][y] == Map2D::TAG)
            {
                m_painter.setPen(QColor(0, 255, 0, 255));
                m_painter.drawEllipse(x*voffset, y*hoffset, 8, 8);
            }*/
        }
    }

    for(int i=0; i < m_tagList.size(); i++)
    {
        Tag tag;
        tag = m_tagList.at(i);
        m_painter.setPen(QColor(0, 255, 0, 255));
        m_painter.drawEllipse(tag.x*voffset - 4, tag.y*hoffset - 4, 8, 8);
    }

    // Draws the mission path
    m_painter.setPen(QColor(0, 255, 0, 255));
    for(int i=0; i<m_missionPath.size(); i++)
    {
        m_painter.drawPoint(m_missionPath.at(i));
    }

    QPen pen;
    pen.setColor(QColor(0,0,255,255));
    pen.setWidth(1);
    m_painter.setPen(pen);

    m_painter.drawEllipse(m_dronePosition.x()*voffset - 6, m_dronePosition.y()*hoffset - 6, 12, 12);
    m_painter.drawEllipse(m_dronePosition.x()*voffset - 4, m_dronePosition.y()*hoffset - 4, 8, 8);
    m_painter.drawEllipse(m_dronePosition.x()*voffset - 2, m_dronePosition.y()*hoffset - 2, 4, 4);


    //m_painter.end();
}

void Environment2D::updateDronePosition(int x, int y)
{
    m_dronePosition = QPoint(x, y);
}


