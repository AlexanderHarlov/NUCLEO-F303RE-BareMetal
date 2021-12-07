/*
 * usart2.c
 *
 *  Created on: Nov 29, 2021
 *      Author: Alex
 */

#include "usart2.h"
#include "common.h"
#include "stm32f3xx.h"

#define USART2_BAUDRATE	115200


static uint16_t calculate_uart_baudrate(USART_TypeDef *USARTx, uint32_t periph_clk, uint32_t baud_rate);
static void uart_set_baudrate(USART_TypeDef *USARTx, uint32_t PeriphClk, uint32_t BaudRate);

void usart2_init(void){
	// Enable clock to PORT A
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN;

	// USART2 TX - PA2, AF7 (GPIO alternative function)
	GPIOA->MODER &= ~GPIO_MODER_MODER2_0;
	GPIOA->MODER |= GPIO_MODER_MODER2_1;
	// Configure alternative function to be AF7 for Pin 2
	GPIOA->AFR[0] |= (0x07UL << GPIO_AFRL_AFRL2_Pos);

	// USART2 RX - PA3, AF7 (GPIO alternative function)
	GPIOA->MODER &= ~GPIO_MODER_MODER3_0;
	GPIOA->MODER |= GPIO_MODER_MODER3_1;
	// Configure alternative function to be AF7 for Pin 3
	GPIOA->AFR[0] |= (0x07UL << GPIO_AFRL_AFRL3_Pos);

	// Enable clock to USART2
	RCC->APB1ENR |= RCC_APB1ENR_USART2EN;

	// Set the baudrate to 115200
	uart_set_baudrate(USART2, APB1_CLK, USART2_BAUDRATE);

	// Enable transmitting and receiving
	USART2->CR1 |= (USART_CR1_TE | USART_CR1_RE);
	// Enable RX interrupt
	USART2->CR1 |= USART_CR1_RXNEIE;
	// Enable UART IRQ in NVIC
	NVIC_EnableIRQ(USART2_IRQn);
	// Enable DMA for TX
	USART2->CR3 |= USART_CR3_DMAT;
	// Enable DMA transfer complete in NVIC
	NVIC_EnableIRQ(DMA1_Channel7_IRQn);
	// Enable UART module
	USART2->CR1 |= USART_CR1_UE;
}

void usart2_write(int ch){
	while(!(USART2->ISR & USART_ISR_TXE)) {}
	USART2->TDR = (ch & 0xFF);
}

char usart2_read(void){
	while(!(USART2->ISR & USART_ISR_RXNE)) {}
	return (USART2->RDR & 0xFF);
}

static uint16_t calculate_uart_baudrate(USART_TypeDef *USARTx, uint32_t periph_clk, uint32_t baud_rate){
	return periph_clk / baud_rate;
}


static void uart_set_baudrate(USART_TypeDef *USARTx, uint32_t periph_clk, uint32_t baud_rate){
	USARTx->BRR = calculate_uart_baudrate(USARTx, periph_clk, baud_rate);
}


int __io_putchar(int ch) {
	usart2_write(ch);
	return ch;
}

void USART2_EXTI26_IRQHandler(void){
	if( USART2->ISR & USART_ISR_RXNE){
		uint16_t key = USART2->RDR;

		if( key == '1' )
			led_set(true);
		else if(key == '0')
			led_set(false);
	}
}
