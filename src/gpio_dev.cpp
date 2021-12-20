/*
 * @Author: your name
 * @Date: 2021-09-24 08:52:37
 * @LastEditTime: 2021-09-24 16:26:37
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \led\main.c
 */
#include <stdio.h>
#include <wiringPi.h>
#include "gpio_dev.h"

//数据结构，hash的基础思想
static char G_PIN_BY_NAME[10] = 
{
	LED_PIN_W,
	LED2_PIN_W,
	KEY1_PIN_W,
	KEY2_PIN_W,
	BEEP_PIN_W	
};

void led_init(void)
{
    pinMode (LED_PIN_W, OUTPUT);
    digitalWrite (LED_PIN_W, LED_OFF);//从实际产品的角度
}

void key_init(void)
{
    pinMode (KEY1_PIN_W, INPUT);
	pullUpDnControl (KEY1_PIN_W, PUD_UP); 
	pinMode (KEY2_PIN_W, INPUT);
	pullUpDnControl (KEY2_PIN_W, PUD_UP);
}

void beep_init(void)
{
	pinMode (BEEP_PIN_W, OUTPUT);
}

void gpio_dev_init(void)
{
	led_init();
	key_init();
	beep_init();
}

#if 1
int gpio_dev_opr(GPIO_DEV_NAME_T name,GPIO_DEV_OPR_T opr)
{
	if(opr == ON || opr == OFF)
	{
		digitalWrite (G_PIN_BY_NAME[name], opr);
	}
	return digitalRead(G_PIN_BY_NAME[name]);
#if 0
	char gpio_dev_pin = -1;
	switch (name)
	{
		case LED:
			gpio_dev_pin = LED_PIN_W;
			break;
		
		default:
			break;
	}
#endif
	
}
#else
void led_opr(LED_STATE_T opr)
{
	digitalWrite (LED_PIN_W, opr);
}

KEY_STATE_T key_read(KEY_PIN_T key)
{
	return digitalRead(key) ;
}

void beep_opr(BEEP_STATE_T opr)
{
	digitalWrite (BEEP_PIN_W, opr);
}
#endif
