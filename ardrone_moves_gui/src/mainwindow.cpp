#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <stdio.h>

MainWindow::MainWindow(ros::NodeHandle *nodehandle, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->nh=nodehandle;
    this->pub_takeoff=this->nh->advertise<std_msgs::Empty>("/ardrone/takeoff",1);
    this->pub_land=this->nh->advertise<std_msgs::Empty>("/ardrone/land", 1);
    this->pub_reset=this->nh->advertise<std_msgs::Empty>("/ardrone/reset", 1);
    this->pub_target=this->nh->advertise<geometry_msgs::Pose>("/position_target",1);
    this->client_enable = this->nh->serviceClient<ardrone_moves::SwitchOnOff>("/position_control/enable");
    this->pub_cmd_vel = this->nh->advertise<geometry_msgs::Twist>("/cmd_vel",1);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::drone_reset()
{
    this->pub_reset.publish(std_msgs::Empty());
}

void MainWindow::emergency()
{
    this->drone_reset();
    this->stopPID();
}

void MainWindow::send_command()
{
    this->pub_cmd_vel.publish(this->command_vel);
}

void MainWindow::fly_x(double x)
{
    this->command_vel.linear.x=x;
    this->send_command();
}

void MainWindow::fly_y(double y){
    this->command_vel.linear.y=y;
    this->send_command();
}
void MainWindow::fly_z(double z)
{
    this->command_vel.linear.z=z;
    this->send_command();
}
void MainWindow::fly_turn(double yaw)
{
    this->command_vel.angular.z=yaw;
    this->send_command();
}

void MainWindow::do_flat_trim()
{
    ros::ServiceClient flat_trim_srv = this->nh->serviceClient<std_srvs::Empty>("/ardrone/flattrim");
    std_srvs::Empty srv;
    if(flat_trim_srv.call(srv)){
        ROS_DEBUG("flat trim request sent");
    }else{
        ROS_DEBUG("flat trim request failed");
    }
}

void MainWindow::do_imu_recalib()
{
    ros::ServiceClient imu_recalib_srv = this->nh->serviceClient<std_srvs::Empty>("/ardrone/imu_recalib");
    std_srvs::Empty srv;
    if(imu_recalib_srv.call(srv)){
        ROS_DEBUG("imu recalib request sent");
    }else{
        ROS_DEBUG("imu recalib request failed");
    }
}

void MainWindow::stopPID(){
    ardrone_moves::SwitchOnOff srv;
    srv.request.enable = false;
    ROS_DEBUG("contacting controller...");
    if(this->client_enable.call(srv)){
        ROS_DEBUG("controller off");
        ui->state->setText("PID off");
    }else{
        ROS_WARN("unable to contact position control node");
        ui->state->setText("error");
    }
}

void MainWindow::on_startPID_but_clicked(){
    ardrone_moves::SwitchOnOff srv;
    srv.request.enable = true;
    ROS_DEBUG("contacting controller...");
    if(this->client_enable.call(srv)){
        ROS_DEBUG("controller on");
        ui->state->setText("PID enabled");
    }else{
        ROS_WARN("unable to contact position control node");
        ui->state->setText("error");
    }
}

void MainWindow::on_stopPID_but_clicked()
{
    this->stopPID();
}

void MainWindow::on_takeoff_but_clicked()
{
    this->drone_takeoff();
}

void MainWindow::on_land_but_clicked()
{
    this->drone_land();
}

void MainWindow::drone_land(){
    this->pub_land.publish(std_msgs::Empty());
}

void MainWindow::drone_takeoff(){
    this->pub_takeoff.publish(std_msgs::Empty());
}
void MainWindow::on_lineEdit_x_editingFinished()
{
    this->target.position.x = ui->lineEdit_x->text().toDouble();
}

void MainWindow::on_lineEdit_y_editingFinished()
{
    this->target.position.y = ui->lineEdit_y->text().toDouble();
}

void MainWindow::on_send_target_but_clicked()
{
    this->pub_target.publish(this->target);
    ui->label_x->setText(QString::number(this->target.position.x));
    ui->label_y->setText(QString::number(this->target.position.y));
    ui->label_z->setText(QString::number(this->target.position.z));
    ui->label_yaw->setText(QString::number(this->target.orientation.z));
}

void MainWindow::on_lineEdit_z_editingFinished()
{
    this->target.position.z=ui->lineEdit_z->text().toDouble();
}

void MainWindow::on_lineEdit_yaw_editingFinished()
{
    this->target.orientation.z=ui->lineEdit_yaw->text().toDouble();
}

void MainWindow::on_lineEdit_yaw_returnPressed()
{
    this->on_lineEdit_yaw_editingFinished();
    this->on_send_target_but_clicked();
}
void MainWindow::on_lineEdit_x_returnPressed()
{
    this->on_lineEdit_x_editingFinished();
    this->on_send_target_but_clicked();
}
void MainWindow::on_lineEdit_y_returnPressed()
{
    this->on_lineEdit_y_editingFinished();
    this->on_send_target_but_clicked();
}
void MainWindow::on_lineEdit_z_returnPressed()
{
    this->on_lineEdit_z_editingFinished();
    this->on_send_target_but_clicked();
}

void MainWindow::on_emergency_but_clicked()
{
    this->emergency();
}


void MainWindow::keyPressEvent(QKeyEvent *event)
{
    switch(event->key()){
    case Qt::Key_Z:
        ROS_DEBUG("press: Z");
        this->fly_x(1);
        break;
    case Qt::Key_S:
        ROS_DEBUG("press: S");
        this->fly_x(-1);
        break;
    case Qt::Key_D:
        this->fly_y(-1);
        break;
    case Qt::Key_Q:
        this->fly_y(1);
        break;
    case Qt::Key_A:
        this->fly_turn(1);
        break;
    case Qt::Key_E:
        this->fly_turn(-1);
        break;
    case Qt::Key_P:
        this->fly_z(1);
        break;
    case Qt::Key_M:
        this->fly_z(-1);
        break;
    default:
        QWidget::keyPressEvent(event);
    }
}
void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    switch(event->key()){
    case Qt::Key_Escape:
        this->emergency();
        break;
    case Qt::Key_Z:
        if(!event->isAutoRepeat()){
            this->fly_x(0);
        }
        break;
    case Qt::Key_S:
        if(!event->isAutoRepeat()){
            this->fly_x(0);
        }
        break;
    case Qt::Key_D:
    case Qt::Key_Q:
        if(event->isAutoRepeat()) break;
        this->fly_y(0);
        break;
    case Qt::Key_A:
    case Qt::Key_E:
        if(event->isAutoRepeat()) break;
        this->fly_turn(0);
        break;
    case Qt::Key_P:
    case Qt::Key_M:
        if(event->isAutoRepeat()) break;
        this->fly_z(0);
        break;
    case Qt::Key_L:
        if(event->isAutoRepeat()) break;
        this->drone_land();
        break;
    case Qt::Key_K:
        if(event->isAutoRepeat()) break;
        this->drone_takeoff();
        break;
    default:
        QWidget::keyReleaseEvent(event);
    }
}

void MainWindow::on_reset_but_clicked()
{
    this->drone_reset();
}

void MainWindow::on_flattrim_but_clicked()
{
    this->do_flat_trim();
}

void MainWindow::on_imu_recalib_but_clicked()
{
    this->do_imu_recalib();
}
