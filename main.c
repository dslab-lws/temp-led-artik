#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include"pwm.h"
#include"gpio.h"

#define BACKLOG 10
#define BUFSIZE 256
#define MAX_DATA_SIZE 256
#define PORT 10000
#define IP_addr "192.168.0.21"
#define device_id "temp-led-artik"

int sockfd;
int ret,len;
struct sockaddr_in servAddr;
char sendBuffer[BUFSIZE], recvBuffer[BUFSIZE];
int recvLen, servLen;
char message[100] = {0,};


void MakeMessage(char *action, char *data){
	int i;
	for(i = 0 ; i < 100 ; i++){
		message[i] = 0;
	}

	int len_id = strlen(device_id);
	int len_ac = strlen(action);
	int len_da = strlen(data);

	char msg_device[] = "{ \"device\" : \"";
	char msg_action[] = "\", \"action\":\"";
	char msg_data[] = "\", \"data\":\"";
	char msg_finish[] = "\" }";

	strcpy(message,msg_device);
	strcat(message,device_id);
	strcat(message,msg_action);
	strcat(message,action);


	if(len_da != 1){
		strcat(message,msg_data);
		strcat(message,data);

	}
	strcat(message,msg_finish);

	len = strlen(message);

	ret = sendto(sockfd, message, len , 0,  ( struct sockaddr*)&servAddr, sizeof( servAddr));

	if (ret == -1) {
		printf("[Error] lwip_send(1),%d\n",errno);
	}

	printf("send_data: %s\n", message);

	if((recvLen=recvfrom(sockfd, recvBuffer, BUFSIZE-1, 0, (struct sockaddr*)&servAddr,(socklen_t*)&servAddr)) == -1) {
	 	   printf("[Error] recvfrom(),%d\n",errno);
	       exit(1);
	    }
	    recvBuffer[recvLen] = '\0';

	    printf("Recevied: %s\n", recvBuffer);

	    strcpy(recvBuffer,'\0');

	    up_mdelay(100);



}

int main() {

	char h[100], t[100];
	char str[100] = {0, };
	int i;

	wifi_main();

	printf("Create the socket...\n");
    if((sockfd=socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
       perror("sock failed");
       exit(1);
    }

	printf("Set up address...\n");

	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_len = sizeof(servAddr);
	servAddr.sin_family = AF_INET;
	servAddr.sin_port = htons(PORT); //port
	servAddr.sin_addr.s_addr = inet_addr(IP_addr); //host

	MakeMessage("detach",0);
	MakeMessage("attach",0);
	MakeMessage("subscribe",0);

	while(1){

		for(i = 0 ; i < 100 ; i++){
			h[i] = 0;
			t[i] = 0;
			str[i] = 0;

			recvLen=recvfrom(sockfd, recvBuffer, BUFSIZE-1, MSG_DONTWAIT, (struct sockaddr*)&servAddr,(socklen_t*)&servAddr);

				if(recvLen > 0){

					recvBuffer[recvLen] = '\0';

					printf("Recevied: %s\n", recvBuffer);

					if (strcmp(recvBuffer,"LEDON") == 0 ){
						gpio_write(47,1);
						printf("*************************LED Is On*************************\n");
					}
					if (strcmp(recvBuffer,"LEDOFF") == 0 ){
						gpio_write(47,0);
						printf("*************************LED Is Off*************************\n");
					}

				}

				up_mdelay(30);
		}





		sprintf(t, "%d", read_adc(0)*330/4096-50);
		strcpy(str,"temp=");
		strcat(str,t);


		MakeMessage("event",str);




	}

	return 0;
}



