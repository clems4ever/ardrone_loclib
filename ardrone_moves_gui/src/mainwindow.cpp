#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <stdio.h>

PositionCtrlGUI::PositionCtrlGUI(ros::NodeHandle *nodehandle, QWidget *parent) :
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

PositionCtrlGUI::~PositionCtrlGUI()
{
    delete ui;
}

void PositionCtrlGUI::drone_reset()
{
    this->pub_reset.publish(std_msgs::Empty());
}

void PositionCtrlGUI::emergency()
{
    this->drone_reset();
    this->stopPID();
}

void PositionCtrlGUI::send_command()
{
    this->pub_cmd_vel.publish(this->command_vel);
}

void PositionCtrlGUI::fly_x(double x)
{
    this->command_vel.linear.x=x;
    this->send_command();
}

void PositionCtrlGUI::fly_y(double y){
    this->command_vel.linear.y=y;
    this->send_command();
}
void PositionCtrlGUI::fly_z(double z)
{
    this->command_vel.linear.z=z;
    this->send_command();
}
void PositionCtrlGUI::fly_turn(double yaw)
{
    this->command_vel.angular.z=yaw;
    this->send_command();
}

void PositionCtrlGUI::do_flat_trim()
{
    ros::ServiceClient flat_trim_srv = this->nh->serviceClient<std_srvs::Empty>("/ardrone/flattrim");
    std_srvs::Empty srv;
    if(flat_trim_srv.call(srv)){
        ROS_DEBUG("flat trim request sent");
    }else{
        ROS_DEBUG("flat trim request failed");
    }
}

void PositionCtrlGUI::do_imu_recalib()
{
    ros::ServiceClient imu_recalib_srv = this->nh->serviceClient<std_srvs::Empty>("/ardrone/imu_recalib");
    std_srvs::Empty srv;
    if(imu_recalib_srv.call(srv)){
        ROS_DEBUG("imu recalib request sent");
    }else{
        ROS_DEBUG("imu recalib request failed");
    }
}

void PositionCtrlGUI::do_toggle_cam(){
    std_srvs::Empty toggle_srv;
    if(ros::service::call("/ardrone/togglecam",toggle_srv)){
        ROS_DEBUG("toggle cam request sent");
    }else{
        ROS_WARN("toggle cam request failed");
    }
}

void PositionCtrlGUI::set_relative_yaw(bool yaw_is_relative){
    ardrone_moves::SwitchOnOff srv;
    srv.request.enable=yaw_is_relative;
    if(ros::service::call("/position_control/enable_relative_yaw",srv)){
        ROS_DEBUG("enable_relative_yaw service call OK");
    }else{
        ROS_WARN("enable_relative_yaw service call failed. Is position_control node launched?");
    }
}

void PositionCtrlGUI::stopPID(){
    ardrone_moves::SwitchOnOff srv;
    srv.request.enable = false;
    if(this->client_enable.call(srv)){
        ROS_DEBUG("controller off");
        ui->state->setText("PID off");
    }else{
        ROS_WARN("unable to contact position control node");
        ui->state->setText("error");
    }
    //stops the drone sending a nul command
    this->command_vel.linear.x=this->command_vel.linear.y=this->command_vel.linear.z=0;
    this->command_vel.angular.x=this->command_vel.angular.y=this->command_vel.angular.z=0;
    this->send_command();
}

void PositionCtrlGUI::on_startPID_but_clicked(){
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

void PositionCtrlGUI::on_stopPID_but_clicked()
{
    this->stopPID();
}

void PositionCtrlGUI::on_takeoff_but_clicked()
{
    this->drone_takeoff();
}

void PositionCtrlGUI::on_land_but_clicked()
{
    this->drone_land();
}

void PositionCtrlGUI::drone_land(){
    this->pub_land.publish(std_msgs::Empty());
}

void PositionCtrlGUI::drone_takeoff(){
    this->pub_takeoff.publish(std_msgs::Empty());
}
void PositionCtrlGUI::on_lineEdit_x_editingFinished()
{
    this->target.position.x = ui->lineEdit_x->text().toDouble();
}

void PositionCtrlGUI::on_lineEdit_y_editingFinished()
{
    this->target.position.y = ui->lineEdit_y->text().toDouble();
}

void PositionCtrlGUI::on_send_target_but_clicked()
{
    this->set_relative_yaw(this->yaw_is_relative);
    this->pub_target.publish(this->target);
    ui->label_x->setText(QString::number(this->target.position.x));
    ui->label_y->setText(QString::number(this->target.position.y));
    ui->label_z->setText(QString::number(this->target.position.z));
    ui->label_yaw->setText(QString::number(this->target.orientation.z));
}

void PositionCtrlGUI::on_lineEdit_z_editingFinished()
{
    this->target.position.z=ui->lineEdit_z->text().toDouble();
}

void PositionCtrlGUI::on_lineEdit_yaw_editingFinished()
{
    this->target.orientation.z=ui->lineEdit_yaw->text().toDouble();
}

void PositionCtrlGUI::on_lineEdit_yaw_returnPressed()
{
    this->on_lineEdit_yaw_editingFinished();
    this->on_send_target_but_clicked();
}
void PositionCtrlGUI::on_lineEdit_x_returnPressed()
{
    this->on_lineEdit_x_editingFinished();
    this->on_send_target_but_clicked();
}
void PositionCtrlGUI::on_lineEdit_y_returnPressed()
{
    this->on_lineEdit_y_editingFinished();
    this->on_send_target_but_clicked();
}
void PositionCtrlGUI::on_lineEdit_z_returnPressed()
{
    this->on_lineEdit_z_editingFinished();
    this->on_send_target_but_clicked();
}

void PositionCtrlGUI::on_emergency_but_clicked()
{
    this->emergency();
}


void PositionCtrlGUI::keyPressEvent(QKeyEvent *event)
{
    switch(event->key()){
    case Qt::Key_Z:
        this->fly_x(1);
        break;
    case Qt::Key_S:
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
void PositionCtrlGUI::keyReleaseEvent(QKeyEvent *event)
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
    case Qt::Key_Comma:
        if(event->isAutoRepeat()) break;
        this->do_toggle_cam();
        break;
    default:
        QWidget::keyReleaseEvent(event);
    }
}

void PositionCtrlGUI::on_reset_but_clicked()
{
    this->drone_reset();
}

void PositionCtrlGUI::on_flattrim_but_clicked()
{
    this->do_flat_trim();
}

void PositionCtrlGUI::on_imu_recalib_but_clicked()
{
    this->do_imu_recalib();
}

void PositionCtrlGUI::on_togglecam_but_clicked()
{
    this->do_toggle_cam();
}

void PositionCtrlGUI::on_relativeYawCheckBox_stateChanged(int arg1)
{
    this->yaw_is_relative=(arg1!=0);
}
