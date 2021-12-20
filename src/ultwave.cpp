#include "ultwave.h"

#include <iostream>
#include <wiringPi.h>

void ult_wave_Init(void)
{
	pinMode(ULT_WAVE_TRIG,OUTPUT);
	digitalWrite(ULT_WAVE_ECHO,LOW);
	
	pinMode(ULT_WAVE_ECHO,INPUT);
	pullUpDnControl(ULT_WAVE_ECHO,PUD_DOWN);
}

double ult_wave_dis(void)
{
	unsigned int time_bigin=0;
	unsigned int time_end=0;
	int error=0;
	
	digitalWrite(ULT_WAVE_TRIG,HIGH);
	delayMicroseconds(10);
	digitalWrite(ULT_WAVE_TRIG,LOW);
	
	time_bigin=micros();
	while(digitalRead(ULT_WAVE_ECHO)==LOW && micros()-time_bigin<100*1000);
	
	if(micros()-time_bigin>=100*1000)
	{
		return -1;
	}
	
	time_bigin=micros();
	while(digitalRead(ULT_WAVE_ECHO)==HIGH && micros()-time_bigin<100*1000);
	if(micros()-time_bigin>=100*1000)
	{
		return -1;
	}
	
	time_end=micros();
	
	return 340.0*(time_end-time_bigin)/2/1000/10;
}
