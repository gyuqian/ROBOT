#ifndef __ANGLESENSOR_H__

#define __ANGLESENSOR_H__

#include <iostream>
#include <wiringPi.h>
#include <wiringPiI2C.h>

void I2C_Setup(void);
int ReadData(int chn);
int ReadREG(int);
int writeClient(char*);

#endif
