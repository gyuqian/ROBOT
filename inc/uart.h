#ifndef __UART_H__

#define __UART_H__

#include <iostream>
#include <wiringSerial.h>

void uartInit(void);
void sendDate(void);
void changeSendDate(char* src);	
void sendStr(char* str);
void uartClode(void);

#endif
