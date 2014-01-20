#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>

#include "ros/ros.h"
#include "std_msgs/Empty.h"
#include "geometry_msgs/Pose.h"
#include "geometry_msgs/Twist.h"
#include "ardrone_moves/SwitchOnOff.h"
#include "std_srvs/Empty.h"

namespace Ui {
class MainWindow;
}

class PositionCtrlGUI : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit PositionCtrlGUI(ros::NodeHandle *nodehandle, QWidget *parent = 0);
    ~PositionCtrlGUI();

 protected:
    void emergency(void);
    void drone_reset(void);

    void stopPID(void);

    //void event(QEvent *event);
    //void mousePressEvent(QMouseEvent *);

    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

    void send_command(void);
    void fly_x(double x);
    void fly_y(double y);
    void fly_z(double z);
    void fly_turn(double yaw);

    void do_imu_recalib(void);
    void do_flat_trim(void);

    void do_toggle_cam(void);
    void set_relative_yaw(bool yaw_is_relative);

    void drone_land(void);
    void drone_takeoff(void);



private slots:
    void on_stopPID_but_clicked();
    void on_startPID_but_clicked();

    void on_takeoff_but_clicked();
    void on_land_but_clicked();

    void on_lineEdit_x_editingFinished();
    void on_lineEdit_y_editingFinished();
    void on_lineEdit_z_editingFinished();
    void on_lineEdit_yaw_editingFinished();
    void on_send_target_but_clicked();

    void on_lineEdit_yaw_returnPressed();
    void on_lineEdit_x_returnPressed();
    void on_lineEdit_y_returnPressed();
    void on_lineEdit_z_returnPressed();

    void on_emergency_but_clicked();


    void on_reset_but_clicked();

    void on_flattrim_but_clicked();

    void on_imu_recalib_but_clicked();

    void on_togglecam_but_clicked();

    void on_relativeYawCheckBox_stateChanged(int arg1);

private:
    Ui::MainWindow *ui;
    ros::NodeHandle *nh;/** ros node handle of the application*/
    ros::Publisher pub_takeoff;
    ros::Publisher pub_land;
    ros::Publisher pub_reset;
    ros::Publisher pub_target;
    ros::Publisher pub_cmd_vel;
    ros::ServiceClient client_enable;

    geometry_msgs::Pose target;
    geometry_msgs::Twist command_vel;

    bool yaw_is_relative;
};

#endif // MAINWINDOW_H
