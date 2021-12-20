#ifndef __ULTWAVE_H__

#define __ULTWAVE_H__

#include <iostream>
#include <wiringPi.h>

#define ULT_WAVE_ECHO 1
#define ULT_WAVE_TRIG 0

void ult_wave_Init(void);
double ult_wave_dis(void);

#endif
