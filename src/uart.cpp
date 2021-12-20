#include "uart.h"

#include <iostream>
#include <wiringSerial.h>
#include <wiringPi.h>
#include <string.h>

using namespace std;

char sendDatestr[200];
int serialFd=-1;

void uartInit(void)
{
	serialFd=serialOpen("/dev/ttyAMA0",115200);
	
	if(serialFd == -1)
	{
		cout<<"Error SerialOpen"<<endl;
	}
	else
	{
		cout<<"Success SerialOpen"<<endl;
	}
}

void sendDate(void)
{
	if(-1!=serialFd)
	{	
		serialPuts(serialFd,sendDatestr);
	}
}

void changeSendDate(char* src)
{
	strcpy(sendDatestr,src);
}

void sendStr(char* str)
{
	if(-1!=serialFd)
	{	
		cout << str <<endl;
		serialPuts(serialFd,str);
	}
}
	
void uartClode(void)
{
	serialClose(serialFd);
	serialFd=-1;
}
