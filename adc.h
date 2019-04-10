/****************************************************************************
*
* Copyright 2018 Primesoft All Rights Reserved.
*
* Filename: adc.h
* Author: enj.park, yr.kim
* Release date: 2018/03/22 
* Version: 1.0
*
****************************************************************************/

#ifndef ADC_H_
#define ADC_H_

#include <errno.h>
#include <fcntl.h>
#include <tinyara/analog/adc.h>
#include <tinyara/analog/ioctl.h>

#define S5J_ADC_MAX_CHANNELS	4

int read_adc(int channel);

#endif /* ADC_H_ */
