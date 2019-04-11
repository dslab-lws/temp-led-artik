#include "A053BasicKit.h"


#define BACKLOG 10
#define BUFSIZE 256
#define MAX_DATA_SIZE 256
#define PORT 10000
#define IP_addr "000.000.000.000" //Gateway IP Address
#define device_id "temp-led-artik" //Device ID

int sockfd;
int ret,len;
struct sockaddr_in servAddr;
char sendBuffer[BUFSIZE], recvBuffer[BUFSIZE];
int recvLen, servLen;
char message[100] = {0,};

void RecvMessage(int Flag){

	if((recvLen=recvfrom(sockfd, recvBuffer, BUFSIZE-1, Flag, (struct sockaddr*)&servAddr,(socklen_t*)&servAddr)) > 0) {

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

}

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
		printf("[Error] sendto(),%d\n",errno);
	}

	printf("send_data: %s\n", message);

	RecvMessage(0);

	up_mdelay(100);



}

int main() {

	char temp[100];
	char str[100];
	int i;
	bool wifiConnected = false;

		while(!wifiConnected)
		{
			ret = mkfifo(CONFIG_WPA_CTRL_FIFO_DEV_REQ,CONFIG_WPA_CTRL_FIFO_MK_MODE);
			if (ret != 0 && ret != -EEXIST)
			{
				printf("mkfifo error for %s: %s",CONFIG_WPA_CTRL_FIFO_DEV_REQ,strerror(errno));
			}
			ret = mkfifo(CONFIG_WPA_CTRL_FIFO_DEV_CFM,CONFIG_WPA_CTRL_FIFO_MK_MODE);
			if (ret != 0 && ret != -EEXIST)
			{
				printf("mkfifo error for %s: %s",CONFIG_WPA_CTRL_FIFO_DEV_CFM,strerror(errno));
			}

			ret = mkfifo(CONFIG_WPA_MONITOR_FIFO_DEV,CONFIG_WPA_CTRL_FIFO_MK_MODE);
			if (ret != 0 && ret != -EEXIST)
			{
				printf("mkfifo error for %s: %s",CONFIG_WPA_MONITOR_FIFO_DEV,strerror(errno));
			}

			if (start_wifi_interface() == SLSI_STATUS_ERROR)
			{
				printf("Connect Wi-Fi failed. Try Again.\n");
			}
			else if(start_wifi_interface() == SLSI_STATUS_SUCCESS)
			{
				wifiConnected = true;
			}
		}

		printf("Connect to Wi-Fi success\n");

		bool ipObtained = false;

		printf("Get IP address\n");

			struct dhcpc_state state;
			void *dhcp_handle;

			while(!ipObtained)
			{
				dhcp_handle = dhcpc_open(NET_DEVNAME);
				ret = dhcpc_request(dhcp_handle, &state);
				dhcpc_close(dhcp_handle);

				if (ret != OK)
				{
					printf("Failed to get IP address\n");
					printf("Try again\n");
					sleep(1);
				}
				else
				{
					ipObtained = true;
				}
			}
			netlib_set_ipv4addr(NET_DEVNAME, &state.ipaddr);
			netlib_set_ipv4netmask(NET_DEVNAME, &state.netmask);
			netlib_set_dripv4addr(NET_DEVNAME, &state.default_router);

			printf("IP address  %s\n", inet_ntoa(state.ipaddr));


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
			temp[i] = 0;
			str[i] = 0;

			RecvMessage(MSG_DONTWAIT);

			up_mdelay(30);
		}





		sprintf(temp, "%d", read_adc(0)*330/4096-50);
		strcpy(str,"temp=");
		strcat(str,temp);


		MakeMessage("event",str);




	}

	return 0;
}



