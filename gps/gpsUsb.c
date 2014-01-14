/**
 * \file gpsusb1.c
 * \brief Test d'une communication par XBee sur un AR Drone 2.0
 * \author Jules Waldhart based on example program by S. Di Mercurio et P.-E. Hladik  ++ J Waldhart
 * \version 1.0
 * \date janvier 2014
 *
 * Pmos GPS board control and configuration tool
 *
 */

#include <stdio.h>		/* Standard input/output definitions */
#include <string.h>		/* String function definitions */
#include <unistd.h>		/* UNIX standard function definitions */
#include <fcntl.h>		/* File control definitions */
#include <errno.h>		/* Error number definitions */
#include <ctype.h>		/* use of isprint() */
#include <termios.h>		/* POSIX terminal control definitions */
#include <stdlib.h>

typedef enum{NO_CHANGE, DEFAULT, GGA, RMC, RMC_GGA}output_sel_t;

int i;
char c;
int com_fd;

char *ComFilename = "/dev/ttyUSB0";
//chaines de configuration de la puce GPS Pmod (global top)
char *pmtk_test = "$PMTK000*32\r\n";	//trame de test
char *pmtk_b9600 = "$PMTK251,9600*17\r\n";	//baudrate 9600
char *pmtk_b38400 = "$PMTK251,38400*27\r\n";	//       38400
char *pmtk_b115200 = "$PMTK251,115200*1F\r\n";	//       115200
char *pmtk_r10hz = "$PMTK220,100*2F\r\n";	//position update 10hz
char *pmtk_r1hz = "$PMTK220,1000*1F\r\n";	//                1hz
char *pmtk_r5hz = "$PMTK220,200*2C\r\n";	//                5hz
char *pmtk_sel_rmc_gga = "$PMTK314,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0*28\r\n";	//n'envoie que les trames NMEA RMC et GGA
char *pmtk_sel_gga = "$PMTK314,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0*29\r\n";	//n'envoie que les trames NMEA GGA
char *pmtk_sel_rmc = "$PMTK314,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0*29\r\n";	//n'envoie que les trames NMEA RMC
char *pmtk_sel_default = "$PMTK314,-1*04\r\n";	//reglage par defaut

/* Variable pour select */
fd_set set;
struct timeval timeout;

void printhelp(void){
	printf("this is a tool for communicating with Pmod GPS device\n"
		"via serial - usb converter. It was developed for ftdi ttl 232R 3V3 chip,\n"
		"but may work with other GPS devices and usb-ttl adapters\n"
		"\n"
		"Option are:\n"
		"-F <device>\tthe device file (default is /dev/ttyUSB0)\n"
		"-b\tset baudrate (9600 38400 115200) default is 9600 baud\n"
		"-B N\tchange GPS chip baudrate and exit N=[9600 | 38400 | 115200]\n"
		"-r\tread communication and print to stdout\n"
		"-h\tprint this help message\n"
		"-t\ttest the GPS sending a null message, then read\n"
		"-S\tput GPS in simple mode : only send GGA and RMC strings equivalent\nto -o simple\n"
		"-u N\tset update rate of gps fix [1 5 10] Hz\n"
		"-o <mode>\tchange output options of NMEA sentences. Possible options\n\tare default, gga, rmc, rmc+gga, simple (equivalent to rmc+gga)\n"
		"\n");
	exit(EXIT_SUCCESS);
}

int open_device(speed_t baudrate)
{
	struct termios options;

	int fd;			/* File descriptor for the port */
	fd = open(ComFilename, O_RDWR | O_NOCTTY | O_NDELAY);
	if (fd == -1) {
		/* Could not open the port. */
		fprintf(stderr, "[Error %d] : Can't open device file %s\n", -1,
			ComFilename);
		return -1;
	} else {
		printf("Opened %s successfully\n", ComFilename);
	}

	tcflush(fd, TCIOFLUSH);
	fcntl(fd, F_SETFL, FNDELAY);
	//memset(&options, 0, sizeof(struct termios));	//mise a zero des options
	tcgetattr(fd, &options); // Get the current options for the port... 
	/*Set the baud rates to 9600 bauds 8N1, no hardware flow control... */
	options.c_cflag = (baudrate | CS8 | CLOCAL | CREAD | HUPCL); 
	//options.c_cflag &= ~CRTSCTS;
	/* Enable the receiver and set local mode...  */
	//options.c_cflag |= (CLOCAL | CREAD);
	/* Set the new options for the port... */
	//options.c_iflag = IGNPAR | IGNBRK;
	options.c_iflag = IGNBRK | IGNCR;
	options.c_oflag = OPOST | ONLCR;
	
	options.c_lflag = ICANON;
	

	if (tcsetattr(fd, TCSANOW, &options) == -1) {
		printf
		    ("impossible de changer la configuration du port serie %s\n", ComFilename);
		exit(EXIT_FAILURE);
	}
	com_fd = fd;
	/* Initialize the file descriptor set. */
	FD_ZERO(&set);
	FD_SET(fd, &set);
	/* Initialize the timeout data structure. */
	timeout.tv_sec = 1;
	timeout.tv_usec = 0;

	return 1;
}

void send_char(char c)
{
	write(com_fd, &c, 1);
}

void send_string(char *s)
{
	do{
		send_char(*s);
	} while (*(s++) != '\n');
}

void get_char(char *c)
{
	int n;
	int delay;

	delay = 0;
	n = 0;

	while (n <= 0) {
		n = read(com_fd, c, 1);
		if (n <= 0) {
			delay++;
			usleep(1000);
		}
	}
}

int main(int argc, char **argv)
{
	char data;
	int c;
	int i = 0;
	speed_t baudrate=B9600;
	char go_simple=0;
	char read=0;
	char set_speed=0;
	char test=0;
	char change_baudrate=0;
	output_sel_t output_mode=NO_CHANGE;

	while ((c = getopt (argc, argv, "b:B:hrtSu:F:o:")) != -1)
		switch (c){
			case 'b':
				if(strncmp(optarg,"9600",4)==0)
					baudrate=B9600;
				else if(strncmp(optarg,"115200",6)==0)
					baudrate=B115200;
				else if(strncmp(optarg,"38400",5)==0)
					baudrate=B38400;
				else
					printhelp();
				break;
			case 'h':
				printhelp();
				break;
			case 'r':
				read=1;
				break;
			case 't':
				test=1;
				break;
			case 'B':
				if(strncmp(optarg,"9600",4)==0)
					change_baudrate='9';
				else if(strncmp(optarg,"115200",6)==0)
					change_baudrate='1';
				else if(strncmp(optarg,"38400",5)==0)
					change_baudrate='3';
				else
					printhelp();
				break;
			case 'S':
				go_simple=1;
				break;
			case 'u':
				set_speed=atoi(optarg);
				if(set_speed!=10 && set_speed!=1 && set_speed!=5)
					printhelp();
				break;
			case 'F':
				ComFilename=optarg;
				break;
			case 'o':
				if(strncmp(optarg,"default",7)==0){
					output_mode=DEFAULT;
				}else if (strncmp(optarg,"rmc",3)==0){
					output_mode=RMC;
				}else if (strncmp(optarg,"gga",3)==0){
					output_mode=GGA;
				}else if ((strncmp(optarg,"rmc+gga",7)==0) || (strncmp(optarg,"simple",6)==0)){
					output_mode = RMC_GGA ;
				}else{
					printhelp();
				}
				break;
			case '?':
				if(optopt=='b')
					fprintf (stderr, "Option -%c requires an argument.\n", optopt);
					else if (isprint (optopt))
						fprintf (stderr, "Unknown option `-%c'.\n", optopt);
					else
						fprintf (stderr,
								"Unknown option character `\\x%x'.\n",
								optopt);
					exit(EXIT_FAILURE);
					break;
					default:
					abort();
					break;
		}

	if(change_baudrate && read)
		printf("You have to restart the program with -b NEWBAUDRATE -r to be able to read the device\n");

	if(set_speed>1 && baudrate==B9600){
		printf("Changing update rate to something else than 1Hz requires a higher baudrate\n");
		exit(EXIT_FAILURE);
	}

	if(open_device(baudrate)!=1){
		exit(EXIT_FAILURE);
	}

	if(go_simple){
		send_string(pmtk_sel_rmc_gga);
	}

	if(test)
		for (i=0;i<10;i++){
			send_string(pmtk_test);
		}

	if(set_speed){
		switch(set_speed){
			case 1:
				send_string(pmtk_r1hz);
				break;
			case 5:
				send_string(pmtk_r5hz);
				break;
			case 10:
				send_string(pmtk_r10hz);
				break;
			default:
				printhelp();
		}
	}

	switch (output_mode){
		case RMC:
			send_string(pmtk_sel_rmc);
			break;
		case GGA:
			send_string(pmtk_sel_gga);
			break;
		case RMC_GGA:
			send_string(pmtk_sel_rmc_gga);
			break;
		case DEFAULT:
			send_string(pmtk_sel_default);
			break;
		default:
			break;
	}

	if(change_baudrate){
		switch (change_baudrate){
			case '3':
				send_string(pmtk_b38400);
				exit(EXIT_SUCCESS);
				break;
			case '9':
				send_string(pmtk_b9600);
				exit(EXIT_SUCCESS);
				break;
			case '1':
				send_string(pmtk_b115200);
				exit(EXIT_SUCCESS);
				break;
		}
	}

	while(read){
		get_char(&data);
		printf("%c", data);
	}
	return 0;
}
