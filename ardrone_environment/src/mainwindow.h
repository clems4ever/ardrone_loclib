#ifndef SETTINGSWIDGET_H
#define SETTINGSWIDGET_H

#include <QWidget>
#include <QMainWindow>

#include <QTableWidget>

#include "cvimageviewer.h"
#include "environment2d.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);

    void closeEvent(QCloseEvent *);

    void fillTagsTable(const QList<Environment2D::Tag> &tagsList);
    
signals:
    void quitAsked();
    void closing();
    
public slots:
    void refreshEnvironmentImage(IplImage *);

private:
    QTableWidget *p_tableWidget;

    CvImageViewer *p_imageViewer;
    
};

#endif // SETTINGSWIDGET_H
