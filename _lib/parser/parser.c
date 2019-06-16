#include "parser.h"

uint8_t line[255];

int parse_line(uint8_t* line, uint8_t symb)
{
	switch (symb)
	{
		case 0x7F:
			line--;
			break;
		
		case 0x0D:
			return 0;
			break;
		
		default:
			*line++ = symb;
			break;
	}
}
