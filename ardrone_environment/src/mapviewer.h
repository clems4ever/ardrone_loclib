#ifndef MAPVIEWER_H
#define MAPVIEWER_H

#include "cvimageviewer.h"

class MapViewer : public CvImageViewer
{
    Q_OBJECT

public:
    MapViewer(QWidget *parent = 0);

protected:
    void mouseMoveEvent(QMouseEvent *ev)
    {
        m_mousex = ev->pos().x();
        m_mousey = ev->pos().y();
        repaint();
    }

    void paintEvent(QPaintEvent *);

public slots:
    void refreshOffsetX(double);
    void refreshOffsetY(double);

    void refreshScaleX(double);
    void refreshScaleY(double);

private:
    int m_offsetx, m_offsety;
    double m_scalex, m_scaley;
};

#endif // MAPVIEWER_H
