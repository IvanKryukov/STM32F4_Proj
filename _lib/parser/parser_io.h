#if !defined PARSER_IO_H
#define PARSER_IO_H

#include "parser.h"
#include "usart_config.h"

#define NL	"\n\r"

void prs_print(unsigned char *out_line);
void prs_print_byte(unsigned char out_byte);
void prs_print_bytes(unsigned char *out_bytes, unsigned char bytes_count);
void prs_print_int(unsigned int out_int);

unsigned char prs_read_byte(void);

#endif

