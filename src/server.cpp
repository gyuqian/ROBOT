#include "uart.h"
#include "file.h"
#include "gpio_dev.h"
#include "robot.h"
#include "ultwave.h"
#include "angleSensor.h"
#include "server.h"

#include <iostream>
#include <stdio.h>
#include <stdlib.h>	
#include <string.h>
#include <sys/types.h>	       /* See NOTES */
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/stat.h>
#include <ctype.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <wiringPi.h>
#include <wiringSerial.h>

#define SER_IP "192.168.12.1"
#define SER_POET 4578

#define ANG_SENSOR_X 0
#define ANG_SENSOR_Y 1
#define ANG_SENSOR_X_NOR 87
#define ANG_SENSOR_Y_NOR 87

using namespace std;

static int error_print(int res, char *err)
{
    if(res == -1) {
        perror(err);
        return -1;
    }
    return 0;
}

classServer::classServer()
{
	classServer::ser_fd=0;
	classServer::cli_fd=0;
}

int classServer::server_socket_init(void)
{
    int res;
    struct sockaddr_in seraddr, cliaddr;
    socklen_t cliaddr_len;
    char buf[BUFSIZ], clie_ip[BUFSIZ];


    ser_fd = socket(AF_INET, SOCK_STREAM, 0);
    error_print(ser_fd, "socket");

    bzero(&seraddr, sizeof(seraddr));
    seraddr.sin_family = AF_INET;
    seraddr.sin_addr.s_addr = htonl(INADDR_ANY);
    seraddr.sin_port = htons(SER_POET);

    res = bind(ser_fd, (struct sockaddr *)&seraddr, sizeof(seraddr));
    error_print(res, "bind");


    res = listen(ser_fd, 128);
    error_print(res, "listen");

	std::cout << "Waiting for Client..." <<std::endl;
    cliaddr_len = sizeof(cliaddr);
    cli_fd = accept(ser_fd, (struct sockaddr *)&cliaddr, &cliaddr_len);
    error_print(cli_fd, "accept");


    printf("client ip:%s,client port:%d\n",
           inet_ntop(AF_INET, &cliaddr.sin_addr.s_addr, clie_ip, sizeof(clie_ip)),
           ntohs(cliaddr.sin_port));

    return 0;
}


int classServer::data_handle(void)
{
    int len=0, i=0;
    int times = 4;
    char buf[1024];

    int ang_x=0;
    int ang_y=0;
    int sum_x=0;
    int sum_y=0;

    while(!len) 
	{

	memset(buf,0,1024);
	cout<<buf<<endl;
        len = read(cli_fd, buf, sizeof(buf));
		
        cout<<"Recv:"<<buf<<endl;
        writeClient(buf);
        
        sum_x =0;
        sum_y=0;
	for(i=0;i<100;i++)
	{
		sum_x += ReadData(ANG_SENSOR_X);
		sum_y += ReadData(ANG_SENSOR_Y);
	}
	
	ang_x=sum_x/100;
	ang_y=sum_y/100;
	
	if(abs(ang_y-ANG_SENSOR_Y_NOR)>10)
		{
			if((ang_y-ANG_SENSOR_Y_NOR)<-10)
			{
				robot_action(STAND_UP_LEFT);
			robot_action(END);
			robot_action(STAND_UP_BEHIND);
				
			robot_action(END);
			}
			else
			{
				robot_action(STAND_UP_RIGHT);
			robot_action(END);
			robot_action(STAND_UP_BEHIND);
				
			robot_action(END);
			}
		}
		
	else if(abs(ang_x-ANG_SENSOR_X_NOR)>10)
		{
			cout<<"X="<<ReadData(ANG_SENSOR_X)<<endl;
			delay(1000);
			cout<<"X="<<ReadData(ANG_SENSOR_X)<<endl;
			delay(1000);
			if((ang_x-ANG_SENSOR_X_NOR)>10)
			{	
				robot_action(STAND_UP_BEHIND);
				robot_action(END);
			}
			
			else
			{
				robot_action(STAND_UP);
				robot_action(END);
			}
		}
        if(strcmp(buf,"0")==0)
        {
			robot_action(GO_AWAY);
		}
		else if(strcmp(buf,"1")==0)
		{
			robot_action(GO_BACK);
		}
		else if(strcmp(buf,"2")==0)
		{
			robot_action(TURN_LEFT);
			robot_action(TURN_LEFT);
			robot_action(TURN_LEFT);
			robot_action(TURN_LEFT);
			robot_action(TURN_LEFT);
			robot_action(TURN_LEFT);
			robot_action(TURN_LEFT);
			robot_action(TURN_LEFT);
			robot_action(END);
		}
		else if(strcmp(buf,"3")==0)
		{
			robot_action(TURN_RIGHT);
			robot_action(TURN_RIGHT);
			robot_action(TURN_RIGHT);
			robot_action(TURN_RIGHT);
			robot_action(TURN_RIGHT);
			robot_action(TURN_RIGHT);
			robot_action(TURN_RIGHT);
			robot_action(TURN_RIGHT);
			robot_action(END);
		}
		else if(strcmp(buf,"4")==0)
		{
			robot_action(MYROBOT_ACT);
		}
		else if(strcmp(buf,"5")==0)
		{
			robot_action(END);
		}
		else if(strcmp(buf,"AUTO")==0)
		{
			robot_action(READY);
			robot_action(GO_BACK);
			robot_action(GO_AWAY);
			robot_action(GO_AWAY);
			robot_action(GO_AWAY);
			robot_action(TURN_LEFT);
			robot_action(TURN_RIGHT);
			robot_action(MYROBOT_ACT);
			robot_action(END);
		}
		else if(strcmp(buf,"QUIT")==0)
		{
			break;
		}
		else if(strcmp(buf,"STAND_UP")==0)
		{
			robot_action(STAND_UP);
			robot_action(END);
		}
		else if(strcmp(buf,"STAND_UP_RIGHT")==0)
		{
			robot_action(STAND_UP_RIGHT);
			robot_action(END);
			robot_action(STAND_UP_BEHIND);
				
			robot_action(END);
		}
		else if(strcmp(buf,"STAND_UP_LEFT")==0)
		{
			robot_action(STAND_UP_LEFT);
			robot_action(END);
			robot_action(STAND_UP_BEHIND);
				
			robot_action(END);
		}
		else
		{
			continue;
		}
	}
    return 0;
}

void classServer::server_socket_close(void)
{
	close(ser_fd);
	close(cli_fd);
}

int classServer::writeClient(char* sendDate)
{
	error_print(write(cli_fd, sendDate, sizeof(sendDate)),"write error");
}
