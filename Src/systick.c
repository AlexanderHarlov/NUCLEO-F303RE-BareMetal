/*
 * systick.c
 *
 *  Created on: Dec 1, 2021
 *      Author: Alex
 */

#include "systick.h"
#include "common.h"
#include "stm32f3xx.h"

// default clock is 8MHz, meaning 8000000 cycles/sec
// for millisecond resolution we delete by 1000 - > 1ms = 8000 cycles
#define SYSTICK_LOAD_VAL_MS		( DEFAULT_SYS_CLK / 1000 )
#define SYSTICK_LOAD_VAL_SEC	( DEFAULT_SYS_CLK )


void systick_delay_ms(int delay){
	// Load the needed cycle count
	SysTick->LOAD = SYSTICK_LOAD_VAL_MS;
	// Clear systick current value register
	SysTick->VAL = 0;
	// Enable systick and use internal clk src
	SysTick->CTRL |= (1 << SysTick_CTRL_ENABLE_Pos) | (1 << SysTick_CTRL_CLKSOURCE_Pos);

	for(int i = 0; i < delay; i++){
		// wait until the COUNTFLAG is set

		while(!(SysTick->CTRL & (1U << SysTick_CTRL_COUNTFLAG_Pos))){

		}
	}

	SysTick->CTRL = 0;
}


void systick_1sec_interrupt_init(void){
	// Load the needed cycle count
	SysTick->LOAD = SYSTICK_LOAD_VAL_SEC;
	// Clear systick current value register
	SysTick->VAL = 0;
	// Enable systick and use internal clk src
	SysTick->CTRL |= (1 << SysTick_CTRL_ENABLE_Pos) | (1 << SysTick_CTRL_CLKSOURCE_Pos);
	// Enable systick interrupt
	SysTick->CTRL |= (1 << SysTick_CTRL_TICKINT_Pos);
}

void SysTick_Handler(void) {
	printf("SysTick second passed! \r\n");
}
