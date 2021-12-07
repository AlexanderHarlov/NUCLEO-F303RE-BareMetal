/*
 * exti.c
 *
 *  Created on: Dec 2, 2021
 *      Author: Alex
 */

#include "exti.h"
#include "common.h"
#include "stm32f3xx.h"

void exti_pc13_init(void){
	// Disable global interrupts
	__disable_irq();
	// EXTI module is part of the SYSCFG module, so enable clock access to SYSCFG
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
	// Select PORTC for EXTI13 (EXTI10-15 share the same EXTI lines
	SYSCFG->EXTICR[3] |= SYSCFG_EXTICR4_EXTI13_PC;
	// Unmask EXTI13
	EXTI->IMR |= EXTI_IMR_IM13;
	// Select falling edge for interrupt
	EXTI->FTSR |= EXTI_FTSR_TR13;
	// Enable line 13 in NVIC
	NVIC_EnableIRQ(EXTI15_10_IRQn);
	// enable global interrupts
	__enable_irq();
}

void EXTI15_10_IRQHandler(){
	if(EXTI->PR & EXTI_PR_PR13){
		// clear interrupt flag for line 13
		EXTI->PR |= EXTI_PR_PR13;
		led_toggle();
		printf("Button was pressed !\r\n");
	}
}
