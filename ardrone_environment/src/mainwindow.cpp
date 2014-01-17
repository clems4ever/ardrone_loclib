#include "mainwindow.h"

#include <QVBoxLayout>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QPushButton>
#include <QFormLayout>
#include <QVariant>

#include "environmentengine.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    QWidget *centralWidget = new QWidget(this);

    QMenuBar *menuBar = new QMenuBar();
    menuBar->setNativeMenuBar(false);

    //menuBar->setVisible(true);
    QMenu *fileMenu = new QMenu("File", menuBar);

    QAction *openConfigurationAction = new QAction("Open", fileMenu);
    QAction *saveConfigurationAction = new QAction("Save", fileMenu);

    QAction *closeAction = new QAction("Quit", fileMenu);

    QAction *settingsAction = new QAction("Settings", menuBar);

    fileMenu->addAction(openConfigurationAction);
    fileMenu->addAction(saveConfigurationAction);
    fileMenu->addSeparator();
    fileMenu->addAction(closeAction);
    menuBar->addMenu(fileMenu);
    menuBar->addAction(settingsAction);
    this->setMenuBar(menuBar);

    p_imageViewer = new MapViewer();
    QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    p_imageViewer->setSizePolicy(sizePolicy);


    //************************ Tag list ****************************

    p_tagsTableWidget = new QTableWidget();
    p_tagsTableWidget->setColumnCount(4);
    p_tagsTableWidget->setAlternatingRowColors(true);


    QPushButton *p_addButton = new QPushButton("Add");
    QPushButton *p_removeButton = new QPushButton("Remove");

    QHBoxLayout *tagButtonshlay = new QHBoxLayout();
    tagButtonshlay->addWidget(p_addButton);
    tagButtonshlay->addWidget(p_removeButton);

    QVBoxLayout *tagvlay = new QVBoxLayout();
    tagvlay->addWidget(p_tagsTableWidget);
    tagvlay->addLayout(tagButtonshlay);


    //**************************************************************


    //************************ Drone info **************************

    QVBoxLayout *infoVLay = new QVBoxLayout();
    QFormLayout *droneInfo = new QFormLayout();
    p_dronePositionLineEdit = new QLineEdit();
    p_dronePositionLineEdit->setEnabled(false);

    p_droneScaleXLineEdit = new QDoubleSpinBox();
    p_droneScaleYLineEdit = new QDoubleSpinBox();
    p_droneScaleXLineEdit->setRange(0.00001, 1000000.0);
    p_droneScaleYLineEdit->setRange(0.00001, 1000000.0);
    p_droneScaleXLineEdit->setValue(1.0);
    p_droneScaleYLineEdit->setValue(1.0);

    p_droneOffsetXLineEdit = new QDoubleSpinBox();
    p_droneOffsetYLineEdit = new QDoubleSpinBox();
    p_droneOffsetXLineEdit->setRange(-DBL_MAX, DBL_MAX);
    p_droneOffsetYLineEdit->setRange(-DBL_MAX, DBL_MAX);

    droneInfo->addRow(new QLabel("Drone position"), p_dronePositionLineEdit);
    droneInfo->addRow(new QLabel("Scale X"), p_droneScaleXLineEdit);
    droneInfo->addRow(new QLabel("Scale Y"), p_droneScaleYLineEdit);

    droneInfo->addRow(new QLabel("Offset X"), p_droneOffsetXLineEdit);
    droneInfo->addRow(new QLabel("Offset Y"), p_droneOffsetYLineEdit);
    infoVLay->addLayout(droneInfo);
    infoVLay->addLayout(tagvlay);
    infoVLay->setMargin(10);

    //**************************************************************

    //********************** CentralWidget **************************

    QHBoxLayout *hbox = new QHBoxLayout();

    hbox->addLayout(infoVLay,2);
    hbox->addWidget(p_imageViewer,7, Qt::AlignCenter);

    hbox->setMargin(0);
    centralWidget->setLayout(hbox);


    //***************************************************************


    this->setCentralWidget(centralWidget);

    connect(closeAction, SIGNAL(triggered()), this, SIGNAL(quitAsked()));
    connect(openConfigurationAction, SIGNAL(triggered()), this, SIGNAL(openConfigurationAsked()));
    connect(saveConfigurationAction, SIGNAL(triggered()), this, SIGNAL(saveConfigurationAsked()));

    connect(p_droneOffsetXLineEdit, SIGNAL(valueChanged(double)), this, SIGNAL(offsetXChanged(double)));
    connect(p_droneOffsetXLineEdit, SIGNAL(valueChanged(double)), p_imageViewer, SLOT(refreshOffsetX(double)));
    connect(p_droneOffsetYLineEdit, SIGNAL(valueChanged(double)), this, SIGNAL(offsetYChanged(double)));
    connect(p_droneOffsetYLineEdit, SIGNAL(valueChanged(double)), p_imageViewer, SLOT(refreshOffsetY(double)));

    connect(p_droneScaleXLineEdit, SIGNAL(valueChanged(double)), this, SIGNAL(scaleXChanged(double)));
    connect(p_droneScaleXLineEdit, SIGNAL(valueChanged(double)), p_imageViewer, SLOT(refreshScaleX(double)));
    connect(p_droneScaleYLineEdit, SIGNAL(valueChanged(double)), this, SIGNAL(scaleYChanged(double)));
    connect(p_droneScaleYLineEdit, SIGNAL(valueChanged(double)), p_imageViewer, SLOT(refreshScaleY(double)));

    connect(p_addButton, SIGNAL(clicked()), this, SIGNAL(addTagAsked()));
    connect(p_removeButton, SIGNAL(clicked()), this, SLOT(removeTag()));

}

/** @brief Gets the closedEvent to quit the application
  */
void MainWindow::closeEvent(QCloseEvent *event)
{
    emit closing();
}

void MainWindow::refreshTagsTable(const QList<EnvironmentEngine::Tag> &tagsList)
{
    disconnect(p_tagsTableWidget, SIGNAL(itemChanged(QTableWidgetItem*)), this, SLOT(validateItemChange(QTableWidgetItem*)));
    p_tagsTableWidget->clear();
    p_tagsTableWidget->setRowCount(tagsList.size());
    QStringList headersList;
    headersList << "Code" << "Value" << "X" << "Y";
    p_tagsTableWidget->setHorizontalHeaderLabels(headersList);
    QTableWidgetItem *item;
    int newRow;
    for(int i=0; i<tagsList.size(); i++)
    {
        item = new QTableWidgetItem(QString("%1").arg(tagsList.at(i).code));
        p_tagsTableWidget->setItem(i, 0, item);
        item = new QTableWidgetItem(QString("%1").arg(tagsList.at(i).value));
        p_tagsTableWidget->setItem(i, 1, item);
        item = new QTableWidgetItem(QString("%1").arg((double)tagsList.at(i).x));
        p_tagsTableWidget->setItem(i, 2, item);
        item = new QTableWidgetItem(QString("%1").arg((double)tagsList.at(i).y));
        p_tagsTableWidget->setItem(i, 3, item);
    }
    connect(p_tagsTableWidget, SIGNAL(itemChanged(QTableWidgetItem*)), this, SLOT(validateItemChange(QTableWidgetItem*)));
}


/** @brief Refreshes the environment image in the GUI
  */
void MainWindow::refreshEnvironmentImage(QImage img)
{
    //cv::Mat m(img);
    //qDebug(QString("Refresh %1, %2").arg(img.size().width()).arg(img.size().height()).toStdString().c_str());
    p_imageViewer->showImage(img);
}

/** @brief Slot that validates the datas that have been modified and emits tagChanged signal
  */
void MainWindow::validateItemChange(QTableWidgetItem *item)
{
    int pos = item->row();
    QString code = p_tagsTableWidget->item(pos, 0)->text();
    QString value = p_tagsTableWidget->item(pos, 1)->text();
    double x = p_tagsTableWidget->item(pos, 2)->text().toDouble();
    double y = p_tagsTableWidget->item(pos, 3)->text().toDouble();
    //qDebug(QString("row %1 has changed, code %2").arg(pos).arg(code).toStdString().c_str());

    emit tagChanged(pos, code, value, x, y);
}

/** @brief Slot that gets the position of the selected line in the table and ask for removing the tag by emitting a signal
  */
void MainWindow::removeTag()
{
    QTableWidgetItem *item = p_tagsTableWidget->currentItem();
    if(item == NULL) return;
    int pos = item->row();
    emit removeTagAsked(pos);
}


/** @brief Refreshes the drone position in the line edit
  */
void MainWindow::refreshDronePosition(const EnvironmentEngine::DoublePoint &p)
{
    p_dronePositionLineEdit->setText(QString("(%1,%2)").arg(p.x()).arg(p.y()));
}


/** @brief Refreshed the offset and scale of the map in the corresponding line edit.
  */
void MainWindow::refreshOffsetAndScale(const EnvironmentEngine::DoublePoint &offset, const EnvironmentEngine::DoublePoint &scale)
{
    p_droneOffsetXLineEdit->setValue(offset.x());
    p_droneOffsetYLineEdit->setValue(offset.y());
    p_droneScaleXLineEdit->setValue(scale.x());
    p_droneScaleYLineEdit->setValue(scale.y());
}

