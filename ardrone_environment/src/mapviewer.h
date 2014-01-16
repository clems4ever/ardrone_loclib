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

public slots:
    void refreshOffsetX(double);
    void refreshOffsetY(double);

    void refreshScaleX(double);
    void refreshScaleY(double);

private:
    QPoint pt1, pt2;
    bool m_holdPressed;

    int m_offsetx, m_offsety;
    double m_scalex, m_scaley;
};

#endif // MAPVIEWER_H
