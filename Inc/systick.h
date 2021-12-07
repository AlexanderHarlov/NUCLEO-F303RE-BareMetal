/*
 * systick.h
 *
 *  Created on: Dec 1, 2021
 *      Author: Alex
 */

#ifndef SYSTICK_H_
#define SYSTICK_H_

extern void systick_delay_ms(int delay);
extern void systick_1sec_interrupt_init(void);

#endif /* SYSTICK_H_ */
