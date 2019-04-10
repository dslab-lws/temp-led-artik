/****************************************************************************
*
* Copyright 2018 Primesoft All Rights Reserved.
*
* Filename: 522_wifiClient.c
* Author: enj.park, yr.kim
* Release date: 2018/03/22
* Version: 1.0
*
****************************************************************************/

#include <stdio.h>
#include "wifi.h"
#define SSID "D.S.Lab"
#define PWD "dslab123"


int wifi_main(int argc, char *argv[]) {
	printf("============= WiFi Test Start =============\n");

	if (wifi_connect(SSID, PWD) != 0) {
		return -1;
	}

	start_dhcp_client();


	printf("============== WiFi Test End ==============\n");

	return 0;
}
