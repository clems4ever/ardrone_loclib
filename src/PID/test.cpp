#include <stdlib.h>
#include <iostream>
#include <fstream>
#include "PID.hpp"

#define MAX_LOOPS 1000

using namespace std;

int main(int argc,char **argv){
	char ok=1;
	int antiloop=0;
	double meas,comm;
	ofstream logfile("data.log",ios::app);
	PID pid_ctrlr(-0.204119152605267,-2.80369590845499,0,10^(-2),-10,10);
	while(ok && ++antiloop<MAX_LOOPS){
		cin >> meas;
		logfile << meas << ",";
		comm = pid_ctrlr.step(1,meas);
		cout << comm << endl;
		logfile << comm << endl;
	}

	logfile.close();
	return 0;
}
