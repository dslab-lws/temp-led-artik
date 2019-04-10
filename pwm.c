/****************************************************************************
*
* Copyright 2018 Primesoft All Rights Reserved.
*
* Filename: pwm.c
* Author: enj.park, yr.kim
* Release date: 2018/03/22 
* Version: 1.0
*
****************************************************************************/

#include "pwm.h"

int pwm_open (int port) {
	int fd;

	switch (port){
		case 0 : fd = open("/dev/pwm0", O_RDWR); break;
		case 1 : fd = open("/dev/pwm1", O_RDWR); break;
		case 2 : fd = open("/dev/pwm2", O_RDWR); break;
		case 3 : fd = open("/dev/pwm3", O_RDWR); break;
		case 4 : fd = open("/dev/pwm4", O_RDWR); break;
		case 5 : fd = open("/dev/pwm5", O_RDWR); break;
		default : break;
	}

	return fd;
}

void pwm_write(int fd, int period, int duty_cycle) {
	int frequency;
	ub16_t duty;
	struct pwm_info_s pwm_info;

	// set pwo_info parameter
	frequency = 1000000 / period;
	duty = duty_cycle * 65536 / period;
	pwm_info.frequency = frequency;
	pwm_info.duty = duty;

	ioctl(fd, PWMIOC_SETCHARACTERISTICS, (unsigned long)((uintptr_t)&pwm_info));
	ioctl(fd, PWMIOC_START);
}

void pwm_close (int fd) {
	ioctl(fd, PWMIOC_STOP);
	close(fd);
}
