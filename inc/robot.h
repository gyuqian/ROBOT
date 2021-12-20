#ifndef __ROBOT_H__

#define __ROBOT_H__
typedef enum
{
	READY=0,
	GO_BACK,
	GO_AWAY,
	TURN_LEFT,
	TURN_RIGHT,
	
	STAND_UP_AHEAD,
	STAND_UP_BEHIND,
	STAND_UP_LEFT,
	STAND_UP_RIGHT,
	
	MYROBOT_ACT,
	STAND_UP,
	END
}ROBOT_ACTION_NAME_T;

extern void robot_action(ROBOT_ACTION_NAME_T act_name);
void robot_get_action(char*,int);
void get_step_delay(int fileline);
#endif
