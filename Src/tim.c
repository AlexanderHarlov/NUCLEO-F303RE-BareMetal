/*
 * tim.c
 *
 *  Created on: Dec 1, 2021
 *      Author: Alex
 */

#include "common.h"
#include "tim.h"
#include "stm32f3xx.h"

void tim2_sec_init(void) {
	// Enable clock to TIM2
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
	// Set prescaler value
	TIM2->PSC = 800 - 1; // 8 000 000 / 8 00 = 10000
	// Set auto-reload value
	TIM2->ARR = 10000 - 1;
	// Clear counter
	TIM2->CNT = 0;
	// Enable timer
	TIM2->CR1 = TIM_CR1_CEN;
}

void tim2_sec_interrupt_init(void) {
	// Enable clock to TIM2
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
	// Set prescaler value
	TIM2->PSC = 800 - 1; // 8 000 000 / 8 00 = 10000
	// Set auto-reload value
	TIM2->ARR = 10000 - 1;	// 10000cycles = 1sec
	// Clear counter
	TIM2->CNT = 0;
	// Enable TIM2 Update interrupt
	TIM2->DIER |= TIM_DIER_UIE;
	// Enable TIM2 interrupt in NVIC
	NVIC_EnableIRQ(TIM2_IRQn);
	// Enable timer
	TIM2->CR1 = TIM_CR1_CEN;
}

// this function will toggle the LED based on TIM2 output compare mode
void tim2_pa5_output_compare_init(void) {
	// Enable clock to port A
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
	// set pin 5, port A as alternative function mode
	GPIOA->MODER &= ~GPIO_MODER_MODER5_0;
	GPIOA->MODER |= GPIO_MODER_MODER5_1;
	// set Pin 5 AF1 (TIM2_CH1)
	GPIOA->AFR[0] |= (0x01U << GPIO_AFRL_AFRL5_Pos);

	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;

	TIM2->PSC = 800 - 1; // 8 000 000 / 8 00 = 10000
	TIM2->ARR = 1000 - 1;	// 1000 cycles = 100ms

	// Set output compare mode
	TIM2->CCMR1 |= (0x03 << TIM_CCMR1_OC1M_Pos);	// 0011 - Toggle mode
	// Enable TIM2 CH1 in compare mode
	TIM2->CCER |= TIM_CCER_CC1E;

	TIM2->CNT = 0;
	TIM2->CR1 = TIM_CR1_CEN;
}

void tim3_pa6_input_capture_init(void) {
	// Enable clock to port A
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
	// set pin 6, port A as alternative function mode
	GPIOA->MODER &= ~GPIO_MODER_MODER6_0;
	GPIOA->MODER |= GPIO_MODER_MODER6_1;
	// set Pin 6 AF2 (TIM3_CH2)
	GPIOA->AFR[0] |= (0x02U << GPIO_AFRL_AFRL6_Pos);

	RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;

	TIM3->PSC = 800 - 1; // 8 000 000 / 8 00 = 10000

	// Set input capture mode, 0x01 - channel 1 is configured as input, IC1 mapped to TI1
	TIM3->CCMR1 |= (0x01U << TIM_CCMR1_CC1S_Pos);
	// Enable TIM3 CH1 in compare mode
	TIM3->CCER |= TIM_CCER_CC1E;
	TIM2->CNT = 0;

	TIM3->CR1 = TIM_CR1_CEN;
}

void TIM2_IRQHandler(void){
	TIM2->SR &= ~(TIM_SR_UIF);
	printf("TIM2 second passed! \r\n");
}
