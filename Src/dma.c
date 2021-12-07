/*
 * dma.c
 *
 *  Created on: Dec 5, 2021
 *      Author: Alex
 */


#include "dma.h"
#include "led.h"
#include "stm32f3xx.h"

void dma_usart2_init(uint32_t src, uint32_t dst, uint32_t len) {
	// USART2 TX is mapped to DMA1_CH7
	// Enable clock access to DMA1
	RCC->AHBENR |= RCC_AHBENR_DMA1EN;
	// Disable DMA1 CH7
	DMA1_Channel7->CCR &= ~DMA_CCR_EN;
	// Wait until disabled
	while (DMA1_Channel7->CCR & DMA_CCR_EN)	;
	// Clear interrupt flags for DMA1 CH7
	DMA1->IFCR |= (DMA_IFCR_CTEIF7 | DMA_IFCR_CHTIF7 | DMA_IFCR_CTCIF7 | DMA_IFCR_CGIF7);
	// Set the destination buffer
	DMA1_Channel7->CPAR = dst;
	// Set the source buffer
	DMA1_Channel7->CMAR = src;
	// Set data length
	DMA1_Channel7->CNDTR = len;
	// Enable memory increment
	DMA1_Channel7->CCR |= DMA_CCR_MINC;
	// Configure transmit direction (from memory to peripherial)
	DMA1_Channel7->CCR |= DMA_CCR_DIR;
	// Enable DMA transfer complete interrupt
	DMA1_Channel7->CCR |= DMA_CCR_TCIE;
	// Enable DMA CH7
	DMA1_Channel7->CCR |= DMA_CCR_EN;
}

void dma_tc_callback(void){
	led_set(true);
}

void DMA1_CH7_IRQHandler(void){
	if(DMA1->ISR & DMA_ISR_TCIF7) {
		DMA1->IFCR |= DMA_IFCR_CTCIF7;
		dma_tc_callback();
	}
}
