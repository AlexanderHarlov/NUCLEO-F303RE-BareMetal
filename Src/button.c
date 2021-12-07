/*
 * button.c
 *
 *  Created on: Nov 29, 2021
 *      Author: Alex
 */

#include "button.h"
#include "stm32f3xx.h"

void button_init(void){
	RCC->AHBENR |= RCC_AHBENR_GPIOCEN;
	// set pin 13, port C as input
	GPIOC->MODER &= ~GPIO_MODER_MODER13_0;
	GPIOC->MODER &= ~GPIO_MODER_MODER13_1;
}

bool button_is_pressed(void){
	return GPIOC->IDR & GPIO_IDR_13 ? false : true;
}
