/**
 * \file gpsusb1.c
 * \brief Test d'une communication par XBee sur un AR Drone 2.0
 * \author S. Di Mercurio et P.-E. Hladik  ++ J Waldhart
 * \version 1.0
 * \date janvier 2014
 *
 * Test d'une communication XBee sur AR Drone
 *
 */

#include <stdio.h>		/* Standard input/output definitions */
#include <string.h>		/* String function definitions */
#include <unistd.h>		/* UNIX standard function definitions */
#include <fcntl.h>		/* File control definitions */
#include <errno.h>		/* Error number definitions */
#include <termios.h>		/* POSIX terminal control definitions */
#include <stdlib.h>

int i;
char c;
int com_fd;

char *RobotComFilename = "/dev/ttyUSB0";
//chaines de configuration de la puce GPS Pmod (global top)
char *pmtk_test = "$PMTK000*32\r\n";	//trame de test
char *pmtk_b9600 = "$PMTK251,9600*17\r\n";	//baudrate 9600
char *pmtk_b38400 = "$PMTK251,38400*27\r\n";	//       38400
char *pmtk_r10hz = "$PMTK220,100*2F\r\n";	//position update 10hz
char *pmtk_r1hz = "$PMTK220,1000*1F\r\n";	//                1hz
char *pmtk_r5hz = "$PMTK220,200*2C\r\n";	//                5hz
char *pmtk_sel_rmc_gga = "$PMTK314,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0*28\r\n";	//n'envoie que les trames NMEA RMC et GGA

/* Variable pour select */
fd_set set;
struct timeval timeout;

void printhelp(void){
	printf("this is a tool to communicate with Pmod GPS device\n"
		"via serial - usb converter. It was developed for ftdi ttl 232R 3V3 chip.\n"
		"\n"
		"Option are:\n"
		"-b	set baudrate (9600 38400 115200)\n"
		"-r	read device and print to stdout\n"
		"-h	print this help message\n"
		"-B N	change GPS chip baudrate and exit N=[9600 | 38400 | 115200]\n"
		"-t	test the GPS sending a null message, then read\n"
		"-S	put GPS in simple mode : only send GGA and RMC strings\n"
		"-u N	set update rate of gps fix [1 5 10] Hz\n"
		"\n");
	exit(EXIT_SUCCESS);
}

int d_robot_open_device(speed_t baudrate)
{
	struct termios options;

	int fd;			/* File descriptor for the port */
	fd = open(RobotComFilename, O_RDWR | O_NOCTTY | O_NDELAY);
	if (fd == -1) {
		/* Could not open the port. */
		fprintf(stderr, "[Error %d] : Can't open device file %s\n", -1,
			RobotComFilename);
		return -1;
	} else {
		printf("Opened %s successfully\n", RobotComFilename);
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
		    ("impossible de changer la configuration du port serie %s\n", RobotComFilename);
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

void d_robot_send_char(char c)
{
	write(com_fd, &c, 1);
}

void d_robot_send_string(char *s)
{
	do{
		d_robot_send_char(*s);
	} while (*(s++) != '\n');
}

void d_robot_get_char(char *c)
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
	printf("C'est parti \n");
	char mode=0;
	char read=0;
	char set_speed=0;
	char test=0;
	char change_baudrate=0;

	while ((c = getopt (argc, argv, "b:B:hrtSs:")) != -1)
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
				mode='S';
				break;
			case 's':
				set_speed=atoi(optarg);
				if(set_speed!=10 && set_speed!=1 && set_speed!=5)
					printhelp();
				/*
				if(strncmp(optarg,"1",1))
					set_speed=1;
				else if(strncmp(optarg,"5",1))
					set_speed=5;
				else if(strncmp(optarg,"10",2))
					set_speed=10;
				else
					printhelp();
					*/
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

	d_robot_open_device(baudrate);

	switch (mode){
			break;
		case 'S':
			d_robot_send_string(pmtk_sel_rmc_gga);
			break;
		default:
			break;
	}

	if(test)
		for (i=0;i<10;i++){
			d_robot_send_string(pmtk_test);
		}

	if(change_baudrate){
		switch (change_baudrate){
			case '3':
				d_robot_send_string(pmtk_b38400);
				exit(EXIT_SUCCESS);
				break;
			case '9':
				d_robot_send_string(pmtk_b9600);
				exit(EXIT_SUCCESS);
				break;
		}
	}

	if(set_speed){
		switch(set_speed){
			case 1:
				d_robot_send_string(pmtk_r1hz);
				break;
			case 5:
				d_robot_send_string(pmtk_r5hz);
				break;
			case 10:
				d_robot_send_string(pmtk_r10hz);
				break;
			default:
				printhelp();
		}
	}


	while(read){
		d_robot_get_char(&data);
		printf("%c", data);
	}
	return 0;
}
