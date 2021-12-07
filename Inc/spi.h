/*
 * spi.h
 *
 *  Created on: Dec 5, 2021
 *      Author: Alex
 */

#ifndef SPI_H_
#define SPI_H_

#include "common.h"

extern void spi1_gpio_init(void);
extern void spi1_config(void);
extern void spi1_transmit(uint8_t* data, uint32_t len);
extern void spi1_receive(uint8_t* data, uint32_t len);
extern void spi1_cs_enable(void);
extern void spi1_cs_disable(void);

#endif /* SPI_H_ */
