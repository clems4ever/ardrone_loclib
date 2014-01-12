#ifndef CVIMAGEVIEWER_H
#define CVIMAGEVIEWER_H

#pragma once
#include <QWidget>
#include <QImage>
#include <QPainter>
#include <QLabel>
#include <QMouseEvent>
#include <opencv2/opencv.hpp>

class CvImageViewer : public QLabel
{
    Q_OBJECT
public:
    explicit CvImageViewer(QWidget *parent = 0) : QLabel(parent)
    {
        setMouseTracking(true);
    }

    QSize sizeHint() const { return _qimage.size(); }
    QSize minimumSizeHint() const { return _qimage.size(); }

    void mouseMoveEvent(QMouseEvent *ev)
    {
        m_mousex = ev->pos().x();
        m_mousey = ev->pos().y();
    }

public slots:

    void showImage(const cv::Mat& image) {
        // Convert the image to the RGB888 format
        switch (image.type()) {
        case CV_8UC1:
            cvtColor(image, _tmp, CV_GRAY2RGB);
            break;
        case CV_8UC3:
            cvtColor(image, _tmp, CV_BGR2RGB);
            break;
        case CV_8UC4:
            cvtColor(image, _tmp, CV_RGBA2BGR);
            break;
        }
        //_tmp = image;

        // QImage needs the data to be stored continuously in memory
        assert(_tmp.isContinuous());
        // Assign OpenCV's image buffer to the QImage. Note that the bytesPerLine parameter
        // (http://qt-project.org/doc/qt-4.8/qimage.html#QImage-6) is 3*width because each pixel
        // has three bytes.
        _qimage = QImage(_tmp.data, _tmp.cols, _tmp.rows, _tmp.cols*3, QImage::Format_RGB888);

        this->setFixedSize(image.cols, image.rows);

        repaint();
    }

protected:
    void paintEvent(QPaintEvent* /*event*/) {
        // Display the image
        QPainter painter(this);
        painter.drawImage(QPoint(0,0), _qimage);
        QRect r(20, 20, 60, 20);
        painter.fillRect(r, QColor(255,255,255, 150));
        painter.setPen(QColor(Qt::blue));
        painter.drawText(r, QString("%1,%2").arg(m_mousex).arg(m_mousey));
        painter.end();
    }

    QImage _qimage;
    cv::Mat _tmp;
    int m_mousex, m_mousey;
};

#endif // CVIMAGEVIEWER_H
