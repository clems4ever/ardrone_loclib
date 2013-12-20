
#ifndef MAP2D_H
#define MAP2D_H

#include <QObject>
#include <QImage>
#include <QSize>
#include <QVariant>
#include "opencv/cv.h"

#define EMPTY_VALUE 0
#define WALL_VALUE 1
#define DRONE_VALUE 2
#define TAG_VALUE 3


class QUrl;
class QString;

class Map2D : public QObject
{
public:
    enum TileType{
        EMPTY = EMPTY_VALUE,
        WALL = WALL_VALUE,
        DRONE = DRONE_VALUE,
        TAG = TAG_VALUE
    };

    struct Tile
    {
        TileType type;
        int id;
        QVariant data;
    };

    struct TagPosition
    {
        int x;
        int y;
    };


    Map2D(QObject * parent = 0);
    virtual ~Map2D();

    void load(const QString& backgroundLayer, const QString& environmentLayer);

    QSize getSize() const;

    const QImage& getBackground() const;

    void toggleWall(const QPoint& p);

    Tile getTile(int x, int y) const;

    void computeEnvironmentImage();


    QList<TagPosition> getTagPositions() const;
    int getTagId(int x, int y) const;
    QVariant getTagValue(int x, int y) const;


    static IplImage* qImage2IplImage(const QImage& qImage);
    IplImage *getCvImage();

private:


    void resizeArray(const QSize& s);

    // Background image of the real environment
    QImage m_backgroundImage;
    // The mask containing the walls and the tags.
    QImage m_maskImage;

    /** Represents the environment image that will be published by ROS
     *
     */
    QImage m_environmentImage;

    // 2D array that represents the map
    Tile **p_tilesArray;

    // List of all the tag positions
    QList<TagPosition> m_tagPositionList;

    // Map size, should be the size of all the images...
    QSize m_size;
};

#endif // MAP2D_H
