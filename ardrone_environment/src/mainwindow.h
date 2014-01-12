#ifndef SETTINGSWIDGET_H
#define SETTINGSWIDGET_H

#include <QWidget>
#include <QMainWindow>

#include <QTableWidget>
#include <QLineEdit>
#include <QLabel>

#include "cvimageviewer.h"
#include "environment2d.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);

    void closeEvent(QCloseEvent *);

    void fillTagsTable(const QList<Environment2D::Tag> &tagsList);
    void refreshDronePosition(const Environment2D::DoublePoint& position);
    
signals:
    void quitAsked();
    void closing();

    void addTagAsked();
    
public slots:
    void refreshEnvironmentImage(IplImage *);


private:
    QTableWidget *p_tagsTableWidget;

    CvImageViewer *p_imageViewer;

    // Drone position line edit displayed in the info widget on the right side
    QLineEdit *p_dronePositionLineEdit;
    QLineEdit *p_droneScaleLineEdit;
    
};

#endif // SETTINGSWIDGET_H
