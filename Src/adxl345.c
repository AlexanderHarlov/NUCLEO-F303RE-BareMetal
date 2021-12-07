#include "adxl345.h"
#include "spi.h"
#include "stm32f3xx.h"


void adxl_read(uint8_t address, uint8_t* rx_data) {
	// Set read operation
	address |= READ_OPERATION;
	// Enable multi-byte
	address |= MULTI_BYTE_EN;
	// Pull CS low
	spi1_cs_enable();
	// Send address
	spi1_transmit(&address, 1);
	// Read 6 bytes
	spi1_receive(rx_data, 6);
	// Pull CS high
	spi1_cs_disable();
}

void adxl_write(uint8_t address, uint8_t val) {
	uint8_t data[2];

	// Enable multi-byte, place address into buffer
	data[0] = address | MULTI_BYTE_EN;
	// Put data
	data[1] = val;
	// Pull CS low
	spi1_cs_enable();
	// Send data
	spi1_transmit(data, 2);
	// Pull CS high
	spi1_cs_disable();
}

void adxl_init(void){
	spi1_gpio_init();
	spi1_config();

	// Set data format range to +-4g
	adxl_write(DATA_FORMAT_R, FOUR_G);
	// Reset all bits
	adxl_write(POWER_CTL_R, RESET_CMD);
	// Configure power control measure bit
	adxl_write(POWER_CTL_R, SET_MEASURE_R);
}
