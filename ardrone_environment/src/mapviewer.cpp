
#include "mapviewer.h"


MapViewer::MapViewer(QWidget *parent) : CvImageViewer(parent)
{
    m_offsetx = 0;
    m_offsety = 0;
    m_scalex = 1.0;
    m_scaley = 1.0;
    m_holdPressed = false;
    setCursor(Qt::BlankCursor);
}

void MapViewer::mouseMoveEvent(QMouseEvent *ev)
{
    pt2 = ev->pos();
    m_mousex = ev->pos().x();
    m_mousey = ev->pos().y();
    repaint();
}

void MapViewer::mousePressEvent(QMouseEvent *ev)
{
    m_holdPressed = true;
    pt1 = ev->pos();
    repaint();
}

void MapViewer::mouseReleaseEvent(QMouseEvent *ev)
{
    m_holdPressed = false;
    repaint();
}

/** @brief reimplements the paintEvent method in order to draw the coordinates in the map and in the real world in meters.
  */
void MapViewer::paintEvent(QPaintEvent *)
{
    // Display the image
    QPainter painter(this);
    painter.drawImage(QPoint(0,0), _qimage);


    QString coordinates = QString("%1,%2 m").arg(m_mousex * m_scalex - m_offsetx).arg(m_mousey * m_scaley - m_offsety);

    painter.setPen(QColor(Qt::white));
    if(m_holdPressed)
    {
        double rx = (pt1.x() - pt2.x()) * m_scalex;
        double ry = (pt1.y() - pt2.y()) * m_scaley;
        double dist = sqrt((rx * rx) + (ry * ry));
        coordinates += QString("\nd=%1 m").arg(dist);
        painter.drawLine(pt1, pt2);
    }


    QRect r(0, 0, 100, 20);
    QRect bound = painter.boundingRect(r, Qt::AlignLeft, coordinates);
    int rx = (m_mousex + bound.width() + 10 >= this->width()) ? m_mousex - bound.width() - 10 : m_mousex + 10;
    int ry = (m_mousey + bound.height() + 10 >= this->height()) ? m_mousey - bound.height() - 10 : m_mousey + 10;
    QRect r1(rx, ry, bound.width(), bound.height());

    painter.fillRect(r1, QColor(255,255,255, 150));
    painter.setPen(QColor(Qt::black));
    painter.drawText(r1, coordinates);

    painter.setPen(QColor(Qt::white));
    painter.drawLine(m_mousex, 0, m_mousex, this->height());
    painter.drawLine(0, m_mousey, this->width(), m_mousey);
    painter.end();
}

void MapViewer::refreshOffsetX(double x)
{
    m_offsetx = x;
}

void MapViewer::refreshOffsetY(double y)
{
    m_offsety = y;
}

void MapViewer::refreshScaleX(double x)
{
    m_scalex = x;
}

void MapViewer::refreshScaleY(double y)
{
    m_scaley = y;
}
