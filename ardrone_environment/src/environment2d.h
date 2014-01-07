#ifndef ENVIRONMENT2D_H
#define ENVIRONMENT2D_H

#include <QObject>
#include <QImage>
#include <QPoint>
#include "opencv/cv.h"


#define EMPTY_VALUE 0
#define WALL_VALUE 1

typedef QList<QPoint> Path;

class Environment2D : public QObject
{
    Q_OBJECT
public:
    struct Tag
    {
        int id;
        QString value;
        int x;
        int y;
    };

    enum Tile
    {
        EMPTY = EMPTY_VALUE,
        WALL = WALL_VALUE
    };

    explicit Environment2D(const QString& background, const QString& wallMask, const QString& tagMask, QObject *parent = 0);
    virtual ~Environment2D();

    Tile getTile(int x, int y) const;
    QList<Tag> getTagsList() const { return m_tagList; }

    QSize getSize() const;
    void setMission(const Path& p);

    void computeImage();

    void updateDronePosition(int x, int y);

    static IplImage* qImage2IplImage(const QImage& qImage);
    IplImage *getCvImage();
    
signals:
    
public slots:
    
private:
    /** Represents the environment image that will be published by ROS
     *
     */
    QImage m_currentEnvironmentImage;

    // Background image of the real environment
    QImage m_backgroundImage;


    // Map size, should be the size of all the images...
    QSize m_size;

    // List of all the tag positions
    QList<Tag> m_tagList;
    QPoint m_dronePosition;

    Path m_missionPath;


    // 2D array that represents the map
    Tile **p_tilesArray;
};

#endif // ENVIRONMENT2D_H
