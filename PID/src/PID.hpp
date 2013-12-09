#include <cfloat>

class PID{

	public:
		PID(double Kp, double Kd, double Ki, double dt, double min_output=DBL_MIN,double max_output=DBL_MAX);

		void reset();
		double step(double setpoint, double measured_value);

	private:
		double integral,previous_error,Kd,Kp,Ki,min_output,max_output,dt;
};
