#include "uart.h"
#include "file.h"
#include "gpio_dev.h"
#include "robot.h"
#include "ultwave.h"
#include "angleSensor.h"
#include "server.h"

#include <iostream>
#include <wiringPi.h>
#include <wiringSerial.h>

using namespace std;

#define USE_SOCKRT


#define ANG_SENSOR_X 1
#define ANG_SENSOR_Y 0
#define ANG_SENSOR_X_NOR 87
#define ANG_SENSOR_Y_NOR 87

int main(int argc,char** argv)
{
	wiringPiSetup();
	gpio_dev_init();
	ult_wave_Init();
	I2C_Setup();
	
	
	#ifdef USE_SOCKRT
	classServer Server1;
	cout << "server_socket_init" <<endl;
	Server1.server_socket_init();
	char sendDate[]="0:GO_AWAY,1:GO_BACK,2:TURN_LEFT,3:TURN_RIGHT,4:MYROBOT_ACT,5:STOP,QUIT";
	cout << sendDate <<endl;
	#endif
	
	int i=0;
	if(argc!=1)
	{
		robot_get_action(argv[1],95);
	}
	
	#ifdef USE_SOCKRT
	Server1.writeClient(sendDate);
	uartInit();
	
	robot_action(READY);
	cout << "Waiting for ACT..."<<endl;
	
	while(gpio_dev_opr(KEY1,READ)==UNPRESS)
	{		
		Server1.data_handle();
	}
	robot_action(END);
	#endif

	Server1.server_socket_close();
	return 0;
}
