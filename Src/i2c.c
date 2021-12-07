/*
 * i2c.c
 *
 *  Created on: Dec 5, 2021
 *      Author: Alex
 */

#include "i2c.h"
#include "common.h"
#include "stm32f3xx.h"

extern void i2c1_init(void){
	// Enable clock access to GPIOB
	RCC->AHBENR |= RCC_AHBENR_GPIOBEN;

	// Set PB8 (SCL) and PB9 (SDA) to alternative function AF4
	GPIOB->MODER &= ~GPIO_MODER_MODER8_0;
	GPIOB->MODER |= GPIO_MODER_MODER8_1;

	GPIOB->AFR[1] |= (0x04UL << GPIO_AFRH_AFRH0_Pos);

	// Set PB8 (SCL) and PB9 (SDA) to alternative function AF4
	GPIOB->MODER &= ~GPIO_MODER_MODER9_0;
	GPIOB->MODER |= GPIO_MODER_MODER9_1;

	GPIOB->AFR[1] |= (0x04UL << GPIO_AFRH_AFRH1_Pos);

	// Set PB8 and PB9 to open drain (push/pull can't operate with multiple devices
	GPIOB->OTYPER |= GPIO_OTYPER_OT_8 | GPIO_OTYPER_OT_9;

	// Enable pull-up for PB8 and PB9 in order to drive the SCL and SDA lines
	GPIOB->PUPDR &=~ GPIO_PUPDR_PUPDR8_0;
	GPIOB->PUPDR |= GPIO_PUPDR_PUPDR8_1;

	GPIOB->PUPDR &=~ GPIO_PUPDR_PUPDR9_0;
	GPIOB->PUPDR |= GPIO_PUPDR_PUPDR9_1;

	// Enable clock for I2C1
	RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;

	// Reset I2C1
	I2C1->CR1 &= I2C_CR1_PE;

}
