#ifndef _uart_included_h_
#define _uart_included_h_

#include <stdint.h>

void uart_init(void);
void uart_putchar(unsigned char data);
unsigned char uart_getchar(void);
void printStr(char* data);
char int_to_char(double in);
#endif
