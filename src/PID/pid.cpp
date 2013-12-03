#include "PID.hpp"

PID::PID(double Kp, double Kd, double Ki, double dt, double min_output,double max_output){
	if(min_output>max_output){
		throw 0;
	}
	this->dt=dt;
	this->Kd=Kd;
	this->Kp=Kp;
	this->Ki=Ki;
	this->min_output=min_output;
	this->max_output=max_output;
	this->reset();
}

void PID::reset(){
	previous_error = 0;
	integral = 0 ;
}

double PID::step(double setpoint, double measured_value){
	double error,output,derivative;
	error = setpoint - measured_value;
	integral = integral + error*dt;
	derivative = (error - previous_error)/dt;
	output = Kp*error + Ki*integral + Kd*derivative;
	//limiation + anti-windup method = disabling integral while not in bounds
	if(output>max_output){
		output=max_output;
		integral=0;
	}else if(output<min_output){
		output=min_output;
		integral=0;
	}
	previous_error = error;
	return output;
}
