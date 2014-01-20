#ifndef SETTINGSWIDGET_H
#define SETTINGSWIDGET_H

#include <QWidget>
#include <QMainWindow>

#include <QTableWidget>
#include <QLineEdit>
#include <QLabel>
#include <QSpinBox>
#include <QPushButton>

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

    void refreshOffsetAndScale(const EnvironmentEngine::DoublePoint& offset, double scale);

signals:
    void quitAsked();
    void openConfigurationAsked();
    void saveConfigurationAsked();
    void closing();

    void addTagAsked();
    void removeTagAsked(int pos);

    void offsetXChanged(double);
    void offsetYChanged(double);

    void scaleChanged(double);

    void tagChanged(int pos, QString code, QString value, double x, double y);

public slots:
    void refreshEnvironmentImage(QImage);
    void validateItemChange(QTableWidgetItem* item);

    void removeTag();

    void autoscale();
    void endAutoscale(QPoint p1, QPoint p2);
    void abortAutoscale();

private:
    EnvironmentEngine *p_environmentEngine;
    QTableWidget *p_tagsTableWidget;

    MapViewer *p_imageViewer;

    // Drone position line edit displayed in the info widget on the right side
    QLineEdit *p_dronePositionLineEdit;
    QLineEdit *p_droneScaleLineEdit;

    QDoubleSpinBox *p_scaleXLineEdit, *p_scaleYLineEdit;
    QDoubleSpinBox *p_droneOffsetXLineEdit, *p_droneOffsetYLineEdit;

    QPushButton *p_autoScaleButton, *p_stopScaleButton;

    bool m_autoscaleEnabled;

};

#endif // SETTINGSWIDGET_H
