#include "simulatorengine.h"


#include <QImageReader>
#include <QCoreApplication>

#include <queue>

ARDroneTrajectory::ARDroneTrajectory(QObject *parent) :
    QObject(parent), m_rosWrapper(this, this)
{
}

ARDroneTrajectory::~ARDroneTrajectory()
{
    m_rosWrapper.exit();
}

void ARDroneTrajectory::start()
{
    m_rosWrapper.start();
}

ARDroneTrajectory::Tile **ARDroneTrajectory::createMap(int width, int height)
{
    p_map = new Tile*[width];
    for(int x=0; x<width; x++)
    {
        p_map[x] = new Tile[height];
    }

    m_size = QSize(width, height);

    return p_map;
}

QList<QPoint> ARDroneTrajectory::getPath(const QPoint &source, const QPoint &destination)
{
    qDebug("Path computation");
    QList<QPoint> path;
    std::priority_queue<Tile*, std::vector<Tile*>, TilePtrComparator > pq;

    int srcx = source.x(), destx = destination.x(), x;
    int srcy = source.y(), desty = destination.y(), y;
    Tile *currentTile, *closestTile = 0;
    bool found = false;

    for(int x=0; x<m_size.width(); x++)
    {
        for(int y=0; y<m_size.height(); y++)
        {
            p_map[x][y].g = -1;
            p_map[x][y].h = 0;
            p_map[x][y].queued = false;
            p_map[x][y].treated = false;
        }
    }

    p_map[srcx][srcy].g = 0;
    p_map[srcx][srcy].h = (destx-srcx)*(destx-srcx) + (desty-srcy)*(desty-srcy);
    p_map[srcx][srcy].x = srcx;
    p_map[srcx][srcy].y = srcy;
    p_map[srcx][srcy].from = 0;

    pq.push(&p_map[srcx][srcy]);

    while(!pq.empty())
    {
        currentTile = pq.top();
        pq.pop();

        x = currentTile->x;
        y = currentTile->y;
        //qDebug(QString("Sel %1,%2").arg(x).arg(y).toStdString().c_str());
        currentTile->treated = true;
        //lastTile = currentTile;
        if(closestTile == 0) closestTile = currentTile;
        if(currentTile->h < closestTile->h && currentTile->g != -1) closestTile = currentTile;

        // We find the destination
        if(currentTile->x == destx && currentTile->y == desty)
        {
            found = true;
            break;
        }

        for(int dx=-1; dx<=1; dx++)
        {
            for(int dy=-1; dy<=1; dy++)
            {
                int tx, ty;
                tx = x + dx;
                ty = y + dy;

                Tile *around = &p_map[tx][ty];

                around->x = tx;
                around->y = ty;
                if(!(dx==0 && dy==0) && !around->treated && around->type == EMPTY)
                {
                    int lastDistance = around->g;


                    int dg = (dx == 0 || dy == 0)? 10 : 14;
                    int h = (destx - tx)*(destx - tx) + (desty - ty)*(desty - ty);
                    int newDistance = currentTile->g + dg;

                    if(newDistance < lastDistance || lastDistance == -1)
                    {
                        around->g = newDistance;
                        around->from = currentTile;
                    }

                    around->h = h;

                    if(!around->queued)
                    {
                        //qDebug(QString("Queued %1,%2,%3").arg(around->x).arg(around->y).arg(around->g + around->h).toStdString().c_str());
                        around->queued = true;
                        pq.push(around);
                    }
                }
            }
        }
    }

    // Get the latest treated tile
    Tile *node = closestTile;

    while(node != 0)
    {
        path.prepend(QPoint(node->x, node->y));
        node = node->from;
    }

    qDebug(QString("PATH %1").arg(path.size()).toStdString().c_str());
    /*for(int i=0; i<path.size(); i++)
    {
        qDebug(QString("%1,%2 ").arg(path.at(i).x()).arg(path.at(i).y()).toStdString().c_str());
    }*/

    return path;
}

