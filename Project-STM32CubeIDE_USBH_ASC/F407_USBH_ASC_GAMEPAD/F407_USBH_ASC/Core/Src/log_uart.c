/*
 * log_uart.c
 *
 *  Created on: Jun 15, 2023
 *      Author: user
 */

#include "log_uart.h"

extern UART_HandleTypeDef huart1;

int __io_putchar(int ch) {
	uint8_t c[1];
	c[0] = ch & 0x00FF;
	HAL_UART_Transmit(&huart1, &*c, 1, 10);
	return ch;
}

int _write(int file, char *ptr, int len) {
	int DataIdx;
	for (DataIdx = 0; DataIdx < len; DataIdx++) {
		__io_putchar(*ptr++);
	}
	return len;
}

int _read(int file, char * ptr, int len){
    (void)(file);
    (void)(ptr);
    (void)(len);
    return -1;
}

