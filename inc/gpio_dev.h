/*
 * @Author: your name
 * @Date: 2021-09-24 11:49:33
 * @LastEditTime: 2021-09-24 16:27:23
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \led\gpio_dev.h
 */
#ifndef __GPIO_DEV_H__
#define __GPIO_DEV_H__

#include <wiringPi.h>
#include <iostream>

#define LED_PIN_W	7
#define LED2_PIN_W	8
#define BEEP_PIN_W	29

typedef enum
{
	LED ,LED2,
	KEY1 ,KEY2,
	BEEP,
}GPIO_DEV_NAME_T;

typedef enum
{
	WRITE = 0,ON,OFF,
	READ = 10,
}GPIO_DEV_OPR_T;

typedef enum
{
	KEY1_PIN_W = 5,KEY2_PIN_W
}KEY_PIN_T;

typedef enum
{
	LED_ON = LOW,LED_OFF
}LED_STATE_T;

typedef enum
{
	BEEP_OFF,BEEP_ON
}BEEP_STATE_T;

typedef enum
{
	PRESS = LOW,UNPRESS
}KEY_STATE_T;

void gpio_dev_init(void);
int gpio_dev_opr(GPIO_DEV_NAME_T name,GPIO_DEV_OPR_T opr);

#endif
