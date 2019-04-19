#include "Printing.h"

#include <stdlib.h>
#include <stdio.h>
#include <usart.h>

#define DBG_UART huart2
unsigned char newline[] = "\r\n";

void dbg_printer(const char* format, va_list args) {
	size_t size = vsnprintf(NULL, 0, format, args) + 1;

	char* buf = malloc(size);
	if(!buf)
		return;

	size = vsnprintf(buf, size, format, args);
	if(size < 1)
		return;

	HAL_UART_Transmit(&DBG_UART, buf, size, 1000);

	free(buf);
}

void dbg_print(const char* format, ...) {
	va_list args;
	va_start(args, format);

	dbg_printer(format, args);

	va_end(args);
}

void dbg_println(const char* format, ...) {
	va_list args;
	va_start(args, format);

	dbg_printer(format, args);

	va_end(args);

	HAL_UART_Transmit(&DBG_UART, newline, 2, 100);
}