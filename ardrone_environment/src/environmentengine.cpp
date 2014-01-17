#include "environmentengine.h"

#include "environmentengine.h"

#include <QImageReader>
#include <QCoreApplication>
#include <QFile>
#include <QDomDocument>
#include <QPen>
#include <QPainter>
#include <QUrl>
#include <QDir>
#include <QFileInfo>

EnvironmentEngine::EnvironmentEngine(QObject *parent) :
    QObject(parent), m_ready(false), m_rosWrapper(this), m_offset(0.0, 0.0), m_scale(1.0, 1.0)
{
    p_tilesArray = 0;
    m_dronePosition = DoublePoint(0,0);

    m_rosWrapper.storeEnvironmentEngine(this);

    connect(&m_rosWrapper, SIGNAL(environmentImagePublished(IplImage*)), this, SIGNAL(environmentImagePublished(IplImage*)));
}

/** @brief Destroys the pointer representing the map
  */
EnvironmentEngine::~EnvironmentEngine()
{
    // shutdowns ros
    m_rosWrapper.end();
    // Wait for the thread to finish
    while(!m_rosWrapper.isFinished());

    freeMemory();
}

/** @brief Starts the ros wrapper thread.
  *
  */
void EnvironmentEngine::start()
{
    m_rosWrapper.start();
}

bool EnvironmentEngine::ready() const
{
    return m_ready;
}

/** Loads the environment with all the parameters already set such as backgroundImageFilename
  */
void EnvironmentEngine::load()
{
    freeMemory();
    p_tilesArray = 0;

    QImage wallMaskImage(m_maskImageFilename);
    m_dronePosition = DoublePoint(0.0,0.0);
    m_lastTagId = 0;

    Tag tag;
    int currentTag = 0;


    m_backgroundImage.load(m_backgroundImageFilename);
    if(m_backgroundImage.isNull())
    {
        qDebug(QString("The image at " + m_backgroundImageFilename + " has not been loaded").toStdString().c_str());
        throw std::exception();
    }

    if(m_backgroundImage.size() != wallMaskImage.size())
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
            if((wallMaskImage.pixel(i, j) & 0x00FFFFFF) == 0){
                p_tilesArray[i][j] = WALL;
            }
            else
            {
                p_tilesArray[i][j] = EMPTY;
            }
        }
    }

    m_ready = true;
}

/** @brief Loads a configuration from a .conf file (XML) where all parameters will be stored.
  *
  */
void EnvironmentEngine::loadConfiguration(const QString &configFilename)
{
    QFile configFile(configFilename);
    QDomDocument document;
    document.setContent(&configFile);

    m_lastTagId = 0;

    QFileInfo configDir(configFilename);
    qDebug(configDir.absoluteDir().path().toStdString().c_str());

    QString backgroundFilename = configDir.path() + "/" + document.elementsByTagName("background").at(0).toElement().attribute("file").toLatin1();
    QString maskFilename = configDir.path() + "/" + document.elementsByTagName("mask").at(0).toElement().attribute("file").toLatin1();
    qDebug(QString("file path = " + backgroundFilename).toStdString().c_str());
    m_backgroundImageFilename = backgroundFilename;
    m_maskImageFilename = maskFilename;

    double offsetx = document.elementsByTagName("offset").at(0).toElement().attribute("x").toDouble();
    double offsety = document.elementsByTagName("offset").at(0).toElement().attribute("y").toDouble();
    m_offset.set(offsetx, offsety);

    double scalex = document.elementsByTagName("scale").at(0).toElement().attribute("x").toDouble();
    double scaley = document.elementsByTagName("scale").at(0).toElement().attribute("y").toDouble();
    m_scale.set(scalex, scaley);

    QDomNodeList list = document.elementsByTagName("tag");
    m_tagList.clear();
    for(int i=0; i<list.size(); i++)
    {
        Tag tag;
        tag.id = m_lastTagId++;
        tag.code = list.at(i).toElement().attribute("code");
        tag.x = list.at(i).toElement().attribute("x").toDouble();
        tag.y = list.at(i).toElement().attribute("y").toDouble();
        tag.value = list.at(i).toElement().attribute("value");
        m_tagList.append(tag);
    }

    this->load();
}

void EnvironmentEngine::saveConfiguration(const QString &configFilename)
{
    QDomDocument doc;
    QDomElement config = doc.createElement("Configuration");
    doc.appendChild(config);

    QDomElement background = doc.createElement("background");
    background.setAttribute("file", QFileInfo(m_backgroundImageFilename).fileName());
    config.appendChild(background);

    QDomElement mask = doc.createElement("mask");
    mask.setAttribute("file", QFileInfo(m_maskImageFilename).fileName());
    config.appendChild(mask);

    QDomElement offset = doc.createElement("offset");
    offset.setAttribute("x", m_offset.x());
    offset.setAttribute("y", m_offset.y());
    config.appendChild(offset);

    QDomElement scale = doc.createElement("scale");
    scale.setAttribute("x", m_scale.x());
    scale.setAttribute("y", m_scale.y());
    config.appendChild(scale);

    QDomElement tags = doc.createElement("tags");
    config.appendChild(tags);
    for(int i=0; i<m_tagList.size(); i++)
    {
        Tag t = m_tagList.at(i);
        QDomElement tag = doc.createElement("tag");
        tag.setAttribute("x", t.x);
        tag.setAttribute("y", t.y);
        tag.setAttribute("code", t.code);
        tag.setAttribute("value", t.value);
        tags.appendChild(tag);
    }

    QFile f(configFilename);
    f.open(QIODevice::WriteOnly);
    f.write(doc.toByteArray());
    f.close();
}


/** @brief Adds a tag into the list of the engine and ask for refreshing the table by emitting a signal
  */
void EnvironmentEngine::addTag()
{
    EnvironmentEngine::Tag t;
    t.id = -1;
    t.x = -1;
    t.y = -1;
    appendTag(t);
    emit tagListUpdated();
}

/** @brief Removes the tag at the given position and ask for refreshing the table by emitting a signal
  */
void EnvironmentEngine::removeTag(int pos)
{
    m_tagList.removeAt(pos);
    emit tagListUpdated();
}



/** @brief Gets the tile at position x and y
  */
EnvironmentEngine::Tile EnvironmentEngine::getTile(int x, int y) const
{
    return p_tilesArray[x][y];
}

/** @brief Appends the tag to the list in the engine
  */
void EnvironmentEngine::appendTag(const Tag &t)
{
    m_tagList.append(t);
}


/** @brief Gets the environment size, i.e. width and height.
  */
const QSize& EnvironmentEngine::getSize() const
{
    return m_size;
}

/** @brief Gets the drone current position
  */
const EnvironmentEngine::DoublePoint &EnvironmentEngine::getDronePosition() const
{
    return m_droneImagePosition;
}

/** @brief Gets the drone position on the image after transform
  */
const EnvironmentEngine::DoublePoint &EnvironmentEngine::getDroneImagePosition() const
{
    return m_dronePosition;
}

/** @brief Gets the offset of the environment
  */
const EnvironmentEngine::DoublePoint &EnvironmentEngine::getOffset() const
{
    return m_offset;
}

/** @brief Gets the stored scale that get the image pixels positions
*/
const EnvironmentEngine::DoublePoint &EnvironmentEngine::getScale() const
{
    return m_scale;
}

/** @brief Sets a mission path which is a list of DoublePoint
  */
void EnvironmentEngine::setMission(const Path &p)
{
    m_missionPath = p;
}


/** @brief Converts an image from QImage to an OpenCV format RGB888 with alpha
  */
IplImage* EnvironmentEngine::qImage2IplImage(const QImage &qImage)
{
    QImage qimg = qImage.copy();
    IplImage *imgHeader = cvCreateImageHeader( cvSize(qimg.width(), qimg.height()), IPL_DEPTH_8U, 4);
    imgHeader->imageData = (char*) qimg.bits();

    uchar* newdata = (uchar*) malloc(sizeof(uchar) * qimg.byteCount());
    memcpy(newdata, qimg.bits(), qimg.byteCount());
    imgHeader->imageData = (char*) newdata;
    return imgHeader;
}

/** @brief Converts a CV image from a Qt Image
  */
IplImage* EnvironmentEngine::getCvImage()
{
    return EnvironmentEngine::qImage2IplImage(m_currentEnvironmentImage);
}

/** @brief Transform a point from real world into a point of the image.
  */

const EnvironmentEngine::DoublePoint EnvironmentEngine::getImagePoint(const EnvironmentEngine::DoublePoint &pt)
{
    DoublePoint p((pt.x() + m_offset.x()) / m_scale.x(), (pt.y() + m_offset.y()) / m_scale.y());
    return p;
}


/** @brief Computes the image representing the environment
  * Draws a background image, a wall mask, the tags represented by circles, the drone by 3 concentric circles
  * and the mission when necessary
  */
void EnvironmentEngine::computeImage()
{
    QPen pen;
    m_currentEnvironmentImage = QImage(m_size, QImage::Format_ARGB32);
    QPainter m_painter(&m_currentEnvironmentImage);

    m_painter.drawImage(0, 0, m_backgroundImage);

    float voffset = ((float)1.0);
    float hoffset = ((float)1.0);

    m_painter.setPen(Qt::black);

    int xmax = m_size.width();
    int ymax = m_size.height();


    // For all pixels on the map, draw the walls.
    for(int y=0; y<ymax; y++)
    {
        for(int x=0; x<xmax; x++)
        {
            if(p_tilesArray[x][y] == EnvironmentEngine::WALL)
            {
                m_painter.setPen(QColor(255, 0, 0, 100));
                m_painter.drawPoint(x*voffset, y*hoffset);
            }
        }
    }

    m_painter.setPen(QColor(0, 255, 0, 255));
    // Draws the tags
    for(int i=0; i < m_tagList.size(); i++)
    {
        Tag tag;
        tag = m_tagList.at(i);
        DoublePoint tp(getImagePoint(DoublePoint(tag.x, tag.y)));
        //qDebug(QString("Tag %1 = %2, %3").arg(i).arg(tp.x()).arg(tp.y()).toStdString().c_str());
        m_painter.drawEllipse(tp.x()*voffset - 4, tp.y()*hoffset - 4, 8, 8);
    }

    // Draws the mission path
    pen.setColor(QColor(0,255,0,255));
    pen.setWidth(2.0);
    m_painter.setPen(pen);
    for(int i=0; i<m_missionPath.size(); i++)
    {
        DoublePoint p = getImagePoint(m_missionPath.at(i));
        m_painter.drawPoint(QPoint(p.x(), p.y()));
    }

    // Draws the drone 3 circles
    pen.setColor(QColor(0,255,0,255));
    pen.setWidth(1);
    m_painter.setPen(pen);

    m_painter.drawEllipse(m_droneImagePosition.x() * voffset - 6, m_droneImagePosition.y() * hoffset - 6, 12, 12);
    m_painter.drawEllipse(m_droneImagePosition.x() * voffset - 4, m_droneImagePosition.y() * hoffset - 4, 8, 8);
    m_painter.drawEllipse(m_droneImagePosition.x() * voffset - 2, m_droneImagePosition.y() * hoffset - 2, 4, 4);


    //m_painter.end();
}

/** @brief Refreshes the drone position
  */
void EnvironmentEngine::updateDronePosition(int x, int y)
{
    m_dronePosition = DoublePoint(x, y);
    m_droneImagePosition = DoublePoint((x + m_offset.x()) / m_scale.x(), (y + m_offset.y()) / m_scale.y());
    emit dronePositionUpdated();
}

/** @brief Sets the 2 coordinates of offset
  */
void EnvironmentEngine::setOffset(double x, double y)
{
    m_offset.setX(x);
    m_offset.setY(y);
}

/** @brief sets the first coordinate of offset
  */
void EnvironmentEngine::setOffsetX(double x)
{
    m_offset.setX(x);
}

/** @brief sets the second coordinate of offset
  */
void EnvironmentEngine::setOffsetY(double y)
{
    m_offset.setY(y);
}

/** @brief Sets the 2 coordinates of scale
  */
void EnvironmentEngine::setScale(double x, double y)
{
    m_scale.setX(x);
    m_scale.setY(y);
}

/** @brief sets the first coordinate of scale
  */
void EnvironmentEngine::setScaleX(double x)
{
    m_scale.setX(x);
}

/** @brief sets the second coordinate of scale
  */
void EnvironmentEngine::setScaleY(double y)
{
    m_scale.setY(y);
}

void EnvironmentEngine::updateTag(int pos, QString code, QString value, double x, double y)
{
    Tag t = m_tagList.at(pos);
    t.code = code;
    t.value = value;
    t.x = x;
    t.y = y;
    m_tagList.replace(pos, t);
}

/** @brief private method that frees the allocated memory
  */
void EnvironmentEngine::freeMemory()
{
    // Free memory
    if(p_tilesArray == 0)
        return;

    for(int i=0; i<m_size.width(); i++)
    {
        delete[] p_tilesArray[i];
    }
    delete[] p_tilesArray;
}
