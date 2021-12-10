#include "compiler_defs.h"
#include "C8051F930_defs.h"
#include "peripherals.h"
#include "SoftwareTimer.h"

sbit LED0 = P0^0;
sbit LED1 = P0^1;

const unsigned char low_reload = LOW_RELOAD_0;
const unsigned char high_reload = HIGH_RELOAD_0;

void main() {
	PCA0MD = 0;	// watchdog disable
	Init_Device();
	P2=P1=P0=0;
	ST_set_timer(0,1000);
	ST_set_timer(1,500);

	while(1) {
//		if(ST_get_flag(0)) {
//			ST_set_timer(0,14);
//			LED0=!LED0;
//		}
//		if(ST_get_flag(1)) {
//			ST_set_timer(1,1000);
//			LED1=!LED1;
//		}
		ST_delay(1000);
		LED1=!LED1;
	}
}

#pragma OT(1)

void TIMER_ISR() interrupt INTERRUPT_TIMER0 { // INTERRUPT_PERIOD_0 ms interrupt period
	ST_timer_run();
	TL0 = low_reload;
  TH0 = high_reload;
}