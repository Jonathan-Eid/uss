#include "SysDelay.h"

void SysTick_Init(uint32_t ticks) {
	
	// Disable SysTick
	SysTick->CTRL = 0;            

	// Set reload register
	SysTick->LOAD = ticks -1;    
	
// Set interrupt priority of SysTick to least urgency (i.e., largest priority value)

	NVIC_SetPriority( SysTick_IRQn, (1<<__NVIC_PRIO_BITS) - 1);

	// Reset the SysTick counter value
	SysTick->VAL = 0;             
// Select processor clock: 1 = processor clock; 0 = external clock

	SysTick->CTRL |= SysTick_CTRL_CLKSOURCE_Msk;
	
	//Enable SysTick Interupt 
	SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk;
	
// Enable SysTick

	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
}


volatile int32_t TimeDelay;

void SysTick_Handle (void) { // SysTick interrupt service routine
 if (TimeDelay > 0) // Prevent it from being negative
 TimeDelay--; // TimeDelay is a global volatile variable
}
void Delay (uint32_t nTime) {
 // nTime: specifies the delay time length
 TimeDelay = nTime; // TimeDelay must be declared as volatile
 while(TimeDelay != 0){} // Busy wait
}
