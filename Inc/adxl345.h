#ifndef ADXL345_H_
#define ADXL345_H_

#include "common.h"

#define DEVICE_ID_R				(0x00)	// Device ID
#define DEVICE_ADDR				(0x53)
#define DATA_FORMAT_R			(0x31)
#define DATA_START_ADDR_R		(0x32)
#define POWER_CTL_R				(0x2D)

#define FOUR_G					(0x01)
#define RESET_CMD				(0x00)
#define SET_MEASURE_R			(0x08)

#define MULTI_BYTE_EN			(0x40)
#define READ_OPERATION			(0x80)

extern void adxl_read(uint8_t address, uint8_t* rx_data);
extern void adxl_write(uint8_t address, uint8_t val);
extern void adxl_init(void);


#endif /* ADXL345_H_ */
