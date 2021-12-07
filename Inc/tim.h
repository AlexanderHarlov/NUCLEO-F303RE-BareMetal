/*
 * tim.h
 *
 *  Created on: Dec 1, 2021
 *      Author: Alex
 */

#ifndef TIM_H_
#define TIM_H_

extern void tim2_sec_init(void);
extern void tim2_sec_interrupt_init(void);
extern void tim2_pa5_output_compare_init(void);
extern void tim3_pa6_input_capture_init(void);

#endif /* TIM_H_ */
