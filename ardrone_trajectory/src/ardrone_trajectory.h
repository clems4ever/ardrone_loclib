#ifndef ENVIRONMENTENGINE_H
#define ENVIRONMENTENGINE_H

#include <QObject>
#include <QPoint>
#include <QSize>

#include "ros_wrapper.h"

class Map2D;

class ARDroneTrajectory : public QObject
{
    Q_OBJECT
public:
    enum TileType
    {
        EMPTY = 0,
        WALL = 1
    };

    class Tile{
    public:
        TileType type;
        int g, h;
        int x,y;
        bool queued;
        bool treated;
        Tile *from;

    };

    class TilePtrComparator
    {
    public:
        bool operator()(const Tile* t1, const Tile* t2)
        {
            return (t1->g + t1->h) > (t2->g + t2->h);
        }
    };

    ARDroneTrajectory(QObject *parent = 0);
    virtual ~ARDroneTrajectory();

    void start();

    Tile **createMap(int width, int height);
    QSize getSize() const { return m_size; }

    QList<QPoint> getPath(const QPoint& source, const QPoint& destination);

signals:

public slots:

private:
    ros_wrapper m_rosWrapper;

    QList<QPoint> m_path;


    Tile **p_map;
    QSize m_size;
};


#endif // ENVIRONMENTENGINE_H
