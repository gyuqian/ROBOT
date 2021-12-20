#include "file.h"
#include "uart.h"
#include "robot.h"
#include "ultwave.h"

#include <iostream>
#include <wiringPi.h>
#include <cstring>

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

using namespace std;
const int fileLineCount=77;

static char G_ACT_GROUP[100][15*7+8] = 
{
	"",
	"",
	//11
	"{G0011#000P1500T0200!#001P1350T0200!#002P1500T0200!#003P1500T0200!#004P1250T0200!#005P1500T0200!#006P1500T0200!}",
	"{G0012#000P1500T0200!#001P1350T0200!#002P1600T0200!#003P1600T0200!#004P1400T0200!#005P1600T0200!#006P1600T0200!}",
	"{G0013#000P1500T0200!#001P1500T0200!#002P1600T0200!#003P1600T0200!#004P1500T0200!#005P1600T0200!#006P1600T0200!}",
	"{G0014#000P1500T0300!#001P1750T0300!#002P1600T0300!#003P1600T0300!#004P1650T0300!#005P1600T0300!#006P1600T0300!}",
	"{G0015#000P1500T0200!#001P1600T0200!#002P1500T0200!#003P1500T0200!#004P1650T0200!#005P1500T0200!#006P1500T0200!}",
	"{G0016#000P1500T0200!#001P1600T0200!#002P1400T0200!#003P1400T0200!#004P1650T0200!#005P1400T0200!#006P1400T0200!}",
	"{G0017#000P1500T0200!#001P1500T0200!#002P1400T0200!#003P1400T0200!#004P1500T0200!#005P1400T0200!#006P1400T0200!}",
	"{G0018#000P1500T0300!#001P1350T0300!#002P1400T0300!#003P1400T0300!#004P1250T0300!#005P1400T0300!#006P1400T0300!}",
};

static int delayTime[100]={0};

/***********************
	READY=0,
	GO_BACK,
	GO_AWAY,
	TURN_LEFT,
	TURN_RIGHT,
	
	STAND_UP_AHEAD,
	STAND_UP_BEHIND,
	
	MYROBOT_ACT,
	STAND_UP,
	END
*/
static char G_ROBOT_ACTION_BY_NAME[100][2] = 
{
	//{act_begin,act_end}
	{0,2},
	{3,10},
	{11,18},
	{11,22},
	{23,26},
	
	{39,41},
	{42,44},
	{62,65},
	{86,89},
	
	{66,82},
	{82,85},
	{0,1}
};

void robot_action(ROBOT_ACTION_NAME_T act_name)
{
	int i=0;
	cout << G_ROBOT_ACTION_BY_NAME[act_name][0]<<G_ROBOT_ACTION_BY_NAME[act_name][1]<<endl;
	for(i = G_ROBOT_ACTION_BY_NAME[act_name][0];i < G_ROBOT_ACTION_BY_NAME[act_name][1];)
	{
		
			sendStr(G_ACT_GROUP[i]);		
			cout << delayTime[i]<<endl;
			delay(delayTime[i]);
			
		
		if((ult_wave_dis()-5.0)>=0.00001||act_name==STAND_UP)
		{
			i++;
		}
		else
		{
			if(i >= G_ROBOT_ACTION_BY_NAME[act_name][0]&&act_name!=STAND_UP)
			{
				i--;
			}
		}
	}
}

void robot_get_action(char* filedir,int fileline)
{
	int fd = 0;
    char buff[1024 * 20];
    int i = 0;
    fd = open(filedir, O_RDONLY);

    char *locate;
    read(fd, buff, sizeof(buff));
    locate = strstr(buff, "G0000=");
    locate = locate + 6;
    memset(G_ACT_GROUP, 0, sizeof(G_ACT_GROUP));

    for(i = 0; i < fileline; i++) {
        memcpy(&G_ACT_GROUP[i], locate, 118-6);
        locate += 119;
	G_ACT_GROUP[i][113]='0';
    }
    get_step_delay(fileline);
}

void get_step_delay(int fileline)
{
	int max=0;
	int i=0;
	int j=0;
	
	for (i=0;i<fileline;i++)
	{
		for(j=1;j<=6;j++)
		{
			if(max<(G_ACT_GROUP[i][16+j*15]-'0')*1000+(G_ACT_GROUP[i][17+j*15]-'0')*100+(G_ACT_GROUP[i][18+j*15]-'0')*10+(G_ACT_GROUP[i][19+j*15]-'0'))
			{
				max=(G_ACT_GROUP[i][16+j*15]-'0')*1000
				+(G_ACT_GROUP[i][17+j*15]-'0')*100
				+(G_ACT_GROUP[i][18+j*15]-'0')*10
				+(G_ACT_GROUP[i][19+j*15]-'0');
			}
		}
		delayTime[i]=max;
		max=0;
	}
}
