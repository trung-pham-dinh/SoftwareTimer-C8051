#include "SoftwareTimer.h"

#include "compiler_defs.h"
#include "C8051F930_defs.h"

static unsigned int counter[ST_NO_TIMERS];
static unsigned char flag[ST_NO_TIMERS];
static unsigned char i;
static unsigned char tick_flag;


void ST_set_timer(unsigned char timer, unsigned int mils) {
	if(timer >= ST_NO_TIMERS) return;
	counter[timer] = mils / ST_TICK_PERIOD;
}

unsigned char ST_get_flag(unsigned char timer) {
	if(timer >= ST_NO_TIMERS) return 0;
	
	if(flag[timer] == 1) {
		flag[timer] = 0;
		return 1;
	}
	return 0;
}

void ST_delay(unsigned int mils) {
	unsigned int delay = mils / ST_TICK_PERIOD;
	while(delay) {
		while(!tick_flag); // prevent reading delay continuously because it will cause the synchronization problem in problem.txt
		tick_flag = 0;
		delay--;
	}
}

#pragma OT(1)
void ST_timer_run() { // must be put in timer ISR
	tick_flag = 1;
	
	for(i=0; i < ST_NO_TIMERS; i++) {
		if(counter[i]) {
			counter[i]--;
			if(!counter[i]) {
				flag[i] = 1;
			}
		}
	}
}