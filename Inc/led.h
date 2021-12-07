/*
 * led.h
 *
 *  Created on: Nov 29, 2021
 *      Author: Alex
 */

#ifndef LED_H_
#define LED_H_

#include "common.h"

extern void led_init();
extern void led_set(bool on);
extern void led_toggle(void);

#endif /* LED_H_ */
