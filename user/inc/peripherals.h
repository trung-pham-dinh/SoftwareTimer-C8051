#ifndef PERIPHERAL
#define PERIPHERAL

#define SYSCLK 								(20000000L/1) // edit this such that suitable with peripheral.c(Hz)
#define TIMER_PRESCALER_0 		4							// edit this such that suitable with peripheral.c
#define INTERRUPT_PERIOD_0 		2						// edit this(ms)

#define TICKS_PER_MIL_0 			(SYSCLK/TIMER_PRESCALER_0/1000) // ticks/mil
#define COUNTER_RELOAD_0 			(-TICKS_PER_MIL_0 * INTERRUPT_PERIOD_0 - 1)
#define HIGH_RELOAD_0 				(COUNTER_RELOAD_0 >> 8)
#define LOW_RELOAD_0 					(COUNTER_RELOAD_0 & 0x00FF)

void Init_Device(void);

#endif