#if !defined PARSER_IO_H
#define PARSER_IO_H

#include "parser.h"
#include "usart_config.h"

#define NL	"\n\r"

void p_print(unsigned char *out_line);
void p_print_byte(unsigned char out_byte);
void p_print_bytes(unsigned char *out_bytes, unsigned char bytes_count);
void p_print_int(unsigned int out_int);

unsigned char p_read_byte(void);

#endif

