#include "parser_io.h"

void prs_print(unsigned char *out_line)
{
	print(out_line);
}

void prs_print_byte(unsigned char out_byte)
{
	print_byte(out_byte);
}

void prs_print_bytes(unsigned char *out_bytes, unsigned char bytes_count)
{
	print_bytes(out_bytes, bytes_count);
}

void prs_print_int(unsigned int out_int)
{
	static unsigned char out_uchar[256] = "";
	static unsigned char *p_first_uchar = &out_uchar[0], buf;
	static int i, n;
	n = 0;
	
	while (out_int != 0)
	{
		*p_first_uchar++ = (unsigned char)(out_int % 10 + 48);
		out_int /= 10;
		n++;
	}
	
	for (i = 0; i < ((n - 1) / 2); i++)
	{
		buf = out_uchar[i];
		out_uchar[i] = out_uchar[n - i - 1];
		out_uchar[n - i - 1] = buf;
	}
	print(out_uchar);
	print(NL);
}

unsigned char prs_read_byte(void)
{
	return read_byte();
}

