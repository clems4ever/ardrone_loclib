#ifndef SETTINGSWIDGET_H
#define SETTINGSWIDGET_H

#include <QWidget>
#include <QMainWindow>

#include <QTableWidget>
#include <QLineEdit>
#include <QLabel>
#include <QSpinBox>

#include "mapviewer.h"
#include "environmentengine.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);

    void closeEvent(QCloseEvent *);

    void refreshTagsTable(const QList<EnvironmentEngine::Tag> &tagsList);
    void refreshDronePosition(const EnvironmentEngine::DoublePoint& position);

    void refreshOffsetAndScale(const EnvironmentEngine::DoublePoint& offset, const EnvironmentEngine::DoublePoint& scale);

signals:
    void quitAsked();
    void openConfigurationAsked();
    void saveConfigurationAsked();
    void closing();

    void addTagAsked();
    void removeTagAsked(int pos);

    void offsetXChanged(double);
    void offsetYChanged(double);

    void scaleXChanged(double);
    void scaleYChanged(double);

    void tagChanged(int pos, QString code, QString value, double x, double y);

public slots:
    void refreshEnvironmentImage(IplImage *);
    void validateItemChange(QTableWidgetItem* item);

    void removeTag();

private:
    EnvironmentEngine *p_environmentEngine;
    QTableWidget *p_tagsTableWidget;

    MapViewer *p_imageViewer;

    // Drone position line edit displayed in the info widget on the right side
    QLineEdit *p_dronePositionLineEdit;
    QLineEdit *p_droneScaleLineEdit;

    QDoubleSpinBox *p_droneScaleXLineEdit, *p_droneScaleYLineEdit;
    QDoubleSpinBox *p_droneOffsetXLineEdit, *p_droneOffsetYLineEdit;

};

#endif // SETTINGSWIDGET_H
