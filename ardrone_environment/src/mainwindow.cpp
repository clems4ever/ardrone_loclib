#include "mainwindow.h"

#include <QVBoxLayout>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QPushButton>
#include <QFormLayout>

#include "environment2d.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    QWidget *centralWidget = new QWidget(this);

    QMenuBar *menuBar = new QMenuBar();
    menuBar->setNativeMenuBar(false);

    //menuBar->setVisible(true);
    QMenu *fileMenu = new QMenu("File", menuBar);
    QAction *closeAction = new QAction("Quit", fileMenu);


    fileMenu->addAction(closeAction);
    menuBar->addMenu(fileMenu);
    this->setMenuBar(menuBar);


    //************************ Drone info **************************

    QFormLayout *droneInfo = new QFormLayout();
    p_dronePositionLineEdit = new QLineEdit();
    p_dronePositionLineEdit->setEnabled(false);

    p_droneScaleLineEdit = new QLineEdit();
    p_droneScaleLineEdit->setEnabled(false);

    droneInfo->addRow(new QLabel("Drone position"), p_dronePositionLineEdit);
    //droneInfo->addRow(new QLabel("Map scale"), p_droneScaleLineEdit);


    //**************************************************************

    //************************ Tag list ****************************

    p_tagsTableWidget = new QTableWidget();
    p_tagsTableWidget->setColumnCount(3);


    QPushButton *p_addButton = new QPushButton("Add");
    connect(p_addButton, SIGNAL(clicked()), this, SIGNAL(addTagAsked()));
    QPushButton *p_removeButton = new QPushButton("Remove");

    QHBoxLayout *tagButtonshlay = new QHBoxLayout();
    tagButtonshlay->addWidget(p_addButton);
    tagButtonshlay->addWidget(p_removeButton);

    QVBoxLayout *tagvlay = new QVBoxLayout();
    tagvlay->addWidget(p_tagsTableWidget);
    tagvlay->addLayout(tagButtonshlay);


    //**************************************************************


    //********************** CentralWidget **************************

    QHBoxLayout *hbox = new QHBoxLayout();
    p_imageViewer = new CvImageViewer();

    hbox->addLayout(tagvlay,3);
    hbox->addWidget(p_imageViewer,7);
    hbox->addLayout(droneInfo,3);
    centralWidget->setLayout(hbox);


    //***************************************************************


    this->setCentralWidget(centralWidget);

    connect(closeAction, SIGNAL(triggered()), this, SIGNAL(quitAsked()));


    //mainLayout->addWidget(p_tableWidget);
}

/** @brief Gets the closedEvent to quit the application
  */
void MainWindow::closeEvent(QCloseEvent *event)
{
    emit closing();
}

void MainWindow::fillTagsTable(const QList<Environment2D::Tag> &tagsList)
{
    p_tagsTableWidget->clear();
    p_tagsTableWidget->setRowCount(tagsList.size());
    QStringList headersList;
    headersList << "Code" << "Value" << "Position";
    p_tagsTableWidget->setHorizontalHeaderLabels(headersList);
    QTableWidgetItem *item;
    int newRow;
    for(int i=0; i<tagsList.size(); i++)
    {
        item = new QTableWidgetItem(QString("%1").arg(tagsList.at(i).id));
        p_tagsTableWidget->setItem(i, 0, item);
        item = new QTableWidgetItem(QString("(%1,%2)").arg((double)tagsList.at(i).x).arg((double)tagsList.at(i).y));
        p_tagsTableWidget->setItem(i, 2, item);
    }
}


/** @brief Refreshes the environment image in the GUI
  */
void MainWindow::refreshEnvironmentImage(IplImage *image)
{
    cv::Mat m(image);
    p_imageViewer->showImage(m);
}

void MainWindow::refreshDronePosition(const Environment2D::DoublePoint &position)
{
    p_dronePositionLineEdit->setText(QString("(%1,%2)").arg(position.x()).arg(position.y()));
}

