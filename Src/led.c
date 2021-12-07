/*
 * led.c
 *
 *  Created on: Nov 29, 2021
 *      Author: Alex
 *
 *  NUCLEO User LED is located on port A, pin 5
 */

#include "led.h"
#include "stm32f3xx.h"



#define LED_PIN_ON (1U<<5)
#define LED_PIN_OFF (1U<<21)

void led_init(void){
	// Enable clock to port A
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
	// set pin 5, port A as output
	GPIOA->MODER |= GPIO_MODER_MODER5_0;
	GPIOA->MODER &= ~GPIO_MODER_MODER5_1;
}

void led_set(bool on){
	GPIOA->BSRR = on ? LED_PIN_ON : LED_PIN_OFF;
}

void led_toggle(void){
	if (GPIOA->ODR & GPIO_ODR_5)
		led_set(false);
	else
		led_set(true);
}
