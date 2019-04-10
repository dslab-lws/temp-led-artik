/****************************************************************************
*
* Copyright 2018 Primesoft All Rights Reserved.
*
* Filename: 522_LWIPServer.c
* Author: enj.park, yr.kim
* Release date: 2018/03/22 
* Version: 1.0
*
****************************************************************************/

#include <net/lwip/sockets.h>
#include <string.h>
#include <stdlib.h>
#include <readline.h>
#include "gpio.h"

#define MAX_DATA_SIZE 100
#define BACKLOG 10

//int server_main(int argc, int port) {
//	int s, new_s;
//	int ret;
//	int on = 1;
//	int sin_size;
//	int recv_num;
//	char recv_data[MAX_DATA_SIZE];
//	char str[MAX_DATA_SIZE];
//	struct sockaddr_in server_addr, client_addr;
//
//	int PORT = 3490;
//
//	// set server address
//	printf("Set server address...\n");
//	memset(&server_addr, 0, sizeof(server_addr));
//	server_addr.sin_len = sizeof(server_addr);
//	server_addr.sin_family = AF_INET;
//	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
//	server_addr.sin_port = htons(PORT);
//
//	// create socket
//	printf("Create socket...\n");
//	s = lwip_socket(AF_INET, SOCK_STREAM, 0);
//	if (s == -1) {
//		printf("[Error] lwip_socket()\n");
//		return -1;
//	}
//
//	// set socket option
//	printf("Set socket option...\n");
//	ret = lwip_setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
//	if (ret == -1) {
//		printf("[Error] lwip_setsockopt()\n");
//		return -1;
//	}
//
//	// bind
//	printf("Bind...\n");
//	ret = lwip_bind(s, (struct sockaddr *)&server_addr, sizeof(server_addr));
//	if (ret == -1) {
//		printf("[Error] lwip_bind()\n");
//		return -1;
//	}
//
//	// listen
//	printf("Listen...\n");
//	ret = lwip_listen(s, BACKLOG);
//	if (ret == -1) {
//		printf("[Error] lwip_listen()\n");
//		return -1;
//	}
//
//	printf("Waiting client [PORT:%d]...\n", PORT);
//	while(1) {
//		sin_size = sizeof(client_addr);
//
//		// accept
//		printf("Accept...\n");
//		new_s = lwip_accept(s, (struct sockaddr *)&client_addr, &sin_size);
//		if (new_s == -1) {
//			printf("[Error] lwip_accept()\n");
//			continue;
//		}
//
//
//
//		while(1) {
//			printf("Receive data...\n");
//			ret = lwip_recv(new_s, recv_data, MAX_DATA_SIZE, 0);
//			if (ret == -1) {
//				printf("[Error] lwip_recv()\n");
//				return -1;
//			}
//			recv_data[ret] = '\0';
//
//			printf("recv_data: %s\n", recv_data);
//
//			 recv_num = atoi(recv_data);
//
//
//			    if (recv_num == 1) {
//
//			    	send(new_s, "fuck", sizeof("fuck"), 0);
//
//
//
//			    }
//
//			    else if (recv_num == 2) {
//
//			        printf("LED OFF\n\n");
//
//			        gpio_write(46, LOW);
//
//			    }
//
//			    else printf("\n");
//
//			if ((strlen(recv_data) == 2) && (recv_data[0] == 'q')) {
//				// close
//				printf("Close socket...\n");
//				ret = lwip_close(new_s);
//				if (ret == -1) {
//					printf("[Error] lwip_close()\n");
//					return -1;
//				}
//
//				return 0;
//
//			}
//		}
//	}
//	return 0;
//}
