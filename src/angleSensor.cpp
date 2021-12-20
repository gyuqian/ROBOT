#include "angleSensor.h"

#include <iostream>
#include <wiringPi.h>
#include <wiringPiI2C.h>

using namespace std;

#define SlaveAddress 0x48

int fd=-1;
void I2C_Setup(void)
{
	fd = wiringPiI2CSetup(SlaveAddress);
}
int ReadData(int chn)
{
	if(chn == 0)
	{
		//wiringPiI2CWrite(fd,0x44);
		return wiringPiI2CReadReg8(fd,0x44);
	}
	else if(chn == 1)
	{
		//wiringPiI2CWrite(fd,0x45);
		return wiringPiI2CReadReg8(fd,0x45);
	}
	else if(chn == 2)
	{
		//wiringPiI2CWrite(fd,0x46);
		return wiringPiI2CReadReg8(fd,0x46);
	}
	else
	{
		return -1;
	}
}

int ReadREG(int chn)
{
		return wiringPiI2CReadReg8(fd,chn);
}
