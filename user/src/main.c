#include "compiler_defs.h"
#include "C8051F930_defs.h"
#include "peripherals.h"
#include "SoftwareTimer.h"

sbit LED0 = P0^0;
sbit LED1 = P0^1;


unsigned long int delay = 100000;
void main() {
	PCA0MD = 0;	// watchdog disable
	Init_Device();
	ST_set_timer(0,1000);
	ST_set_timer(1,500);
	
	
	
	while(1) {
		if(ST_get_flag(0)) {
			ST_set_timer(0,14);
			LED0=!LED0;
		}
		if(ST_get_flag(1)) {
			ST_set_timer(1,500);
			LED1=!LED1;
		}
		
	}
}


void TIMER_ISR() interrupt INTERRUPT_TIMER0 { // 1ms interrupt period
	timer_run();
	TL0 = LOW_RELOAD_0;
  TH0 = HIGH_RELOAD_0;
}