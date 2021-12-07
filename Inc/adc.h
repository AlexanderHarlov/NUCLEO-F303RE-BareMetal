/*
 * adc.h
 *
 *  Created on: Dec 1, 2021
 *      Author: Alex
 */

#ifndef ADC_H_
#define ADC_H_

#include "stdint.h"

extern void adc_init(void);
extern void adc_start_single_conv(void);
extern uint32_t adc_read(void);

#endif /* ADC_H_ */
