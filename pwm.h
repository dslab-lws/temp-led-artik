/****************************************************************************
*
* Copyright 2018 Primesoft All Rights Reserved.
*
* Filename: pwm.h
* Author: enj.park, yr.kim
* Release date: 2018/03/22 
* Version: 1.0
*
****************************************************************************/

#ifndef PWM_H_
#define PWM_H_

#include <fcntl.h>
#include <tinyara/pwm.h>

#define ENABLE	1
#define DISABLE	0

int pwm_open (int port);
void pwm_write(int fd, int period, int duty_cycle);
void pwm_close (int fd);

#endif /* PWM_H_ */
