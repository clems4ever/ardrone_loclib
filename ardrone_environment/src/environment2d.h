#ifndef ENVIRONMENT2D_H
#define ENVIRONMENT2D_H

#include <QObject>
#include <QImage>
#include <QPoint>
#include "opencv/cv.h"


#define EMPTY_VALUE 0
#define WALL_VALUE 1






class Environment2D : public QObject
{
    Q_OBJECT
public:
    struct Tag
    {
        int id;
        int code;
        QString value;
        int x;
        int y;
    };

    enum Tile
    {
        EMPTY = EMPTY_VALUE,
        WALL = WALL_VALUE
    };

    // Like QPoint with doubles
    class DoublePoint
    {
    public:
        DoublePoint()
        {
            m_x = 0.0;
            m_y = 0.0;
        }

        DoublePoint(double x, double y)
        {
            m_x = x;
            m_y = y;
        }

        double x() const { return m_x; }
        double y() const { return m_y; }

        void setX(double x) { m_x = x; }
        void setY(double y) { m_y = y; }

        void set(double x, double y) { m_x = x; m_y = y; }

        double m_x, m_y;
    };

    typedef QList<Environment2D::DoublePoint> Path;


    explicit Environment2D(const QString& background, const QString& wallMask, const QString& tagMask, QObject *parent = 0);
    virtual ~Environment2D();

    Tile getTile(int x, int y) const;
    QList<Tag> getTagsList() const { return m_tagList; }
    void appendTag(const Tag& t);

    const QSize& getSize() const;
    const DoublePoint& getDronePosition() const;
    const DoublePoint& getScale() const;
    void setMission(const Path& p);



    void computeImage();

    void updateDronePosition(int x, int y);

    static IplImage* qImage2IplImage(const QImage& qImage);
    IplImage *getCvImage();
    
signals:
    void dronePositionUpdated();
    
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
    QSize m_imageSize;

    // List of all the tag positions
    QList<Tag> m_tagList;
    DoublePoint m_dronePosition;

    Path m_missionPath;


    // 2D array that represents the map
    Tile **p_tilesArray;

    DoublePoint m_scale;

    QPoint m_offset;

    int m_lastTagId;
};

#endif // ENVIRONMENT2D_H
