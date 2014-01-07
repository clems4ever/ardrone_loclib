#include "mainwindow.h"

#include <QVBoxLayout>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QPushButton>

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

    p_tableWidget = new QTableWidget();
    p_tableWidget->setColumnCount(2);
    QStringList headersList;
    headersList << "ID" << "Value";
    p_tableWidget->setHorizontalHeaderLabels(headersList);

    fileMenu->addAction(closeAction);
    menuBar->addMenu(fileMenu);
    this->setMenuBar(menuBar);

    //********************** CentralWidget **************************

    QHBoxLayout *hbox = new QHBoxLayout();
    p_imageViewer = new CvImageViewer();

    hbox->addWidget(p_tableWidget);
    hbox->addWidget(p_imageViewer);
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
    for(int i=0; i<tagsList.size(); i++)
    {
        p_tableWidget->insertRow(0);
        //p_tableWidget->item(0, 0)->setText(QString("%1").arg(tagsList.at(i).id));
    }
}


/** @brief Refreshes the environment image in the GUI
  */
void MainWindow::refreshEnvironmentImage(IplImage *image)
{
    cv::Mat m(image);
    p_imageViewer->showImage(m);
}
