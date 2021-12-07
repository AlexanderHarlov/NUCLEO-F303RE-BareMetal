/*
 * spi.c
 *
 *  Created on: Dec 5, 2021
 *      Author: Alex
 */

/* SPI1 Pins:
 * PA5 - SCK
 * PA6 - MISO
 * PA7 - MOSI
 * PA9 - CS
 *
 * All pins are AF5 (except PA9 - output)
 * Baud rate - pclk/2 = 4Mhz
 */

#include "spi.h"
#include "stm32f3xx.h"

void spi1_gpio_init(void){
	// Enable clock to PORT A
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN;

	// SPI1 SCK
	GPIOA->MODER &= ~GPIO_MODER_MODER5_0;
	GPIOA->MODER |= GPIO_MODER_MODER5_1;
	GPIOA->AFR[0] |= (0x05UL << GPIO_AFRL_AFRL5_Pos);

	// SPI1 MISO
	GPIOA->MODER &= ~GPIO_MODER_MODER6_0;
	GPIOA->MODER |= GPIO_MODER_MODER6_1;
	GPIOA->AFR[0] |= (0x05UL << GPIO_AFRL_AFRL6_Pos);

	// SPI1 MOSI
	GPIOA->MODER &= ~GPIO_MODER_MODER7_0;
	GPIOA->MODER |= GPIO_MODER_MODER7_1;
	GPIOA->AFR[0] |= (0x05UL << GPIO_AFRL_AFRL7_Pos);

	// SPI1 CS
	GPIOA->MODER |= GPIO_MODER_MODER9_0;
	GPIOA->MODER &= ~GPIO_MODER_MODER9_1;
}

void spi1_config(void){
	// Enable clock for SPI1
	RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;
	// ADXL uses CPOL = 1 and CPHA = 1
	SPI1->CR1 |= SPI_CR1_CPHA | SPI_CR1_CPOL;
	// Set full duplex mode
	SPI1->CR1 &= ~SPI_CR1_RXONLY;
	// MSB first
	SPI1->CR1 &= ~SPI_CR1_LSBFIRST;
	// Set microcontroller as master
	SPI1->CR1 |= SPI_CR1_MSTR;
	// Enable 8bit data format
	//0110: 7-bit
	//0111: 8-bit and so on
	SPI1->CR2 |= (0x07 << SPI_CR2_DS_Pos);
	// Enable software slave managment
	SPI1->CR1 |= SPI_CR1_SSM;
	// Internally select the slave - SSI bit is forced onto the NSS pin, and NSS is ignored
	SPI1->CR1 |= SPI_CR1_SSI;
	// Enable SPI1 module
	SPI1->CR1 |= SPI_CR1_SPE;
}

void spi1_transmit(uint8_t* data, uint32_t len){
	uint32_t iter = 0;
	uint32_t temp = 0;

	while( iter < len ){
		// Wait until TXE is set - meaning transmitted data
		while(!(SPI1->SR & SPI_SR_TXE)) ;

		// Write data to the data register
		SPI1->DR = data[iter];
		iter++;
	}

	// Wait until TXE is set - meaning transmitted data
	while(!(SPI1->SR & SPI_SR_TXE)) ;

	// Wait until BUSY flag is down
	while(SPI1->SR & SPI_SR_BSY) ;

	// Clear OVR flag (not enabled irq for that)
	temp = SPI1->DR;
	temp = SPI1->SR;
}

void spi1_receive(uint8_t* data, uint32_t len){
	while( len ){
		// send dummy data
		SPI1->DR = 0;
		// Wait for RXNE flag to be set
		while(!(SPI1-> SR & SPI_SR_RXNE)) ;
		// Read data from DR
		*data++ = SPI1->DR;
		len--;
	}
}

void spi1_cs_enable(void){
	// CS is inverted, so low level will select the slave
	GPIOA->ODR &= ~GPIO_ODR_9;
}

void spi1_cs_disable(void){
	// CS is inverted, so high level will deselect the slave
	GPIOA->ODR |= GPIO_ODR_9;
}
