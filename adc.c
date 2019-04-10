/****************************************************************************
*
* Copyright 2018 Primesoft All Rights Reserved.
*
* Filename: adc.c
* Author: enj.park, yr.kim
* Release date: 2018/03/22 
* Version: 1.0
*
****************************************************************************/

#include "adc.h"

int read_adc(int channel) {
	int fd, ret;
	struct adc_msg_s sample[S5J_ADC_MAX_CHANNELS];
	int32_t data;
	size_t readsize;
	ssize_t nbytes;

	fd = open("/dev/adc0", O_RDONLY);
	if (fd < 0) {
		printf("%s: open failed: %d\n", __func__, errno);
		return -1;
	}

	for (;;) {
		ret = ioctl(fd, ANIOC_TRIGGER, 0);
		if (ret < 0) {
			printf("%s: ioctl failed: %d\n", __func__, errno);
			close(fd);
			return -1;
		}

		readsize = S5J_ADC_MAX_CHANNELS * sizeof(struct adc_msg_s);
		nbytes = read(fd, sample, readsize);
		if (nbytes < 0) {
			if (errno != EINTR) {
				printf("%s: read failed: %d\n", __func__, errno);
				close(fd);
				return -1;
			}
		} else if (nbytes == 0) {
			printf("%s: No data read, Ignoring\n", __func__);
		} else {
			int nsamples = nbytes / sizeof(struct adc_msg_s);
			if (nsamples * sizeof(struct adc_msg_s) != nbytes) {
				printf("%s: read size=%ld is not a multiple of sample size=%d, Ignoring\n", __func__, (long)nbytes, sizeof(struct adc_msg_s));
			} else {
				int i;
				for (i = 0; i < nsamples; i++) {
					if (sample[i].am_channel == channel) {
						data = sample[i].am_data;
						//printf("Sensor Value : %d \n",data);
						close(fd);
						return data;
					}
				}
			}
		}
	}

	return 0;
}
