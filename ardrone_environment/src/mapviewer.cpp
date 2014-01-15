
#include "mapviewer.h"


MapViewer::MapViewer(QWidget *parent) : CvImageViewer(parent)
{
    m_offsetx = 0;
    m_offsety = 0;
    m_scalex = 1.0;
    m_scaley = 1.0;
    setCursor(Qt::BlankCursor);
}

void MapViewer::paintEvent(QPaintEvent *)
{
    // Display the image
    QPainter painter(this);
    painter.drawImage(QPoint(0,0), _qimage);

    painter.setPen(QColor(Qt::blue));
    QRect r(20, 20, 90, 20);

    painter.fillRect(r, QColor(255,255,255, 150));
    painter.drawText(r, QString("%1,%2 px").arg(m_mousex).arg(m_mousey));
    r = QRect(20, 40, 90, 20);
    painter.fillRect(r, QColor(255,255,255, 150));
    painter.drawText(r, QString("%1,%2 m").arg(m_mousex * m_scalex - m_offsetx).arg(m_mousey * m_scaley - m_offsety));

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
