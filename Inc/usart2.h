/*
 * usart2.h
 *
 *  Created on: Nov 29, 2021
 *      Author: Alex
 */

#ifndef USART2_H_
#define USART2_H_

extern void usart2_init(void);
extern void usart2_write(int ch);
extern char usart2_read(void);

#endif /* USART2_H_ */
