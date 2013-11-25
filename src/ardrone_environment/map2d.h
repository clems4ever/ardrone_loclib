#ifndef MAP2D_H
#define MAP2D_H

#include <QObject>
#include <QImage>
#include <QSize>
#include <QVariant>

class QUrl;
class QString;

class Map2D : public QObject
{
public:
    enum TileType{
        EMPTY, WALL, DRONE, TAG
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


    QList<TagPosition> getTagPositions() const;
    int getTagId(int x, int y) const;
    QVariant getTagValue(int x, int y) const;

private:


    void resizeArray(const QSize& s);

    QImage m_backgroundImage;
    QImage m_environmentImage;

    Tile **p_tilesArray;

    QList<TagPosition> m_tagPositionList;


    QSize m_size;
};

#endif // MAP2D_H
