/*
 * adc.c
 *
 *  Created on: Dec 1, 2021
 *      Author: Alex
 */

#include "common.h"
#include "adc.h"
#include "stm32f3xx.h"

void adc_init(void){
	// Configure ADC GPIO pin

	// Enable clock to GPIOA
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN;

	GPIOA->MODER |= GPIO_MODER_MODER1_0;
	GPIOA->MODER |= GPIO_MODER_MODER1_1;

	// Configure ADC module
	RCC->AHBENR |= RCC_AHBENR_ADC12EN;

	// Configure sequence start
	ADC1->SQR1 |= (0x0F << ADC_SQR1_SQ1_Pos);
	ADC1->SQR1 |= (0 << ADC_SQR1_L_Pos);

	ADC1->CR |= ADC_CR_ADEN;
}

void adc_start_single_conv(void){
	ADC1->CR |= ADC_CR_ADSTART;
}

uint32_t adc_read(void){
	while (!(ADC1->ISR & ADC_ISR_EOC)) ;
	return ADC1->DR;
}
