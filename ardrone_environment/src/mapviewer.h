#ifndef MAPVIEWER_H
#define MAPVIEWER_H

#include "cvimageviewer.h"

class MapViewer : public CvImageViewer
{
    Q_OBJECT

public:
    MapViewer(QWidget *parent = 0);

protected:
    void mouseMoveEvent(QMouseEvent *ev);
    void mousePressEvent(QMouseEvent *ev);
    void mouseReleaseEvent(QMouseEvent *ev);

    void paintEvent(QPaintEvent *);

signals:
    void measurePoints(QPoint p1, QPoint p2);
    void clickedPoint(QPoint p);

public slots:
    void refreshOffsetX(double);
    void refreshOffsetY(double);

    void refreshScale(double);

private:
    QPoint pt1, pt2;
    bool m_holdPressed;

    int m_offsetx, m_offsety;
    double m_scale;
};

#endif // MAPVIEWER_H
