#include "parser.h"
#include "parser_io.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BACKSPASE_KEY	0x7F
#define ENTER_KEY			0x0D

parser_struct parser_line;

/***** Variables *****/

unsigned char cmd_idx_names[ALL_COMMANDS][16] = 
{
	"unknown\0",
	"help\0",
	"list\0"
};

unsigned char cmd_parser_prm_name[ALL_PARAMETERS][10] = 
{ 
	" ", 	// unknown parameter
	"h"	// help - to get help of command
};

static unsigned char input_line[255], start_line[256], sub_line[32];
static unsigned char *p_input = &input_line[0];
static char status = 0;

/*********************/

static void prs_copy_to_start_line(unsigned char *extern_line)
{
	int i = 0;
	
	while (*extern_line)
		start_line[i++] = *extern_line++;
}

void parser_catch_sign(unsigned char *sign)
{
	if (*sign == ENTER_KEY)	// if user pressed 'Enter' 
	{
		p_print("\n\r");
		p_input = &input_line[0];
		prs_copy_to_start_line(input_line);
		memset(input_line, 0, 255);
		status = 1;
	}
	else if (*sign == BACKSPASE_KEY)
	{
		if (p_input > &input_line[0]) 
		{
			p_print_byte(0x7F);
			p_input--;
			*p_input = 0;
		}
	}
	else 							// if pressed another key
	{
		p_print_byte(*sign);
		*p_input++ = *sign;
	}	
}

static unsigned char* select_subline(unsigned char *src, unsigned char *dst)
{
	memset(sub_line, 0, 32);
	dst = &sub_line[0];
	
	if (*src == ' ')
		src++;
	
	while ((*src != ' ') && (*src != 0))
		*dst++ = *src++;
	
	return src;
}

static cmd_idx_type define_cmd_parser_index(unsigned char *cmd_line)
{
	int i;
	
	for (i = 0; i < ALL_COMMANDS; i++) 
	{
		if ((strstr((const char *)cmd_line, (const char *)cmd_idx_names[i]) != NULL) && 
				(strcmp((const char *)cmd_line, (const char *)cmd_idx_names[i]) == 0)) 
		{
			return ((cmd_idx_type) i);
		}
	}
	return cmd_unknown;	
}

static int define_cmd_parser_parameter(unsigned char *cmd_line, 
                                       parser_struct *user_parser_struct)
{
	int i;
	unsigned char minus_line[1] = "-";
    
	if (strstr((const char *)cmd_line, (const char *)minus_line) != NULL) {
		for (i = 0; i < ALL_PARAMETERS; i++) {
			if (strstr((const char *)cmd_line, (const char *)cmd_parser_prm_name[i]) != NULL) {
				user_parser_struct->cmd_prm = (cmd_prm_type)i;
			}
		}
	}
	else {
		return -1; 
	}
	
  return 0;
}

void parser_routine(void)
{
	unsigned char *psrc = &start_line[0], *pdst = &sub_line[0];
	int res = 0;
	
	if (status != 0)
	{
		status = 0;		
		
		/****** catch the command ******/
		psrc = select_subline(psrc, pdst);
		parser_line.cmd_idx = define_cmd_parser_index(pdst);
		
		/***** catch the parameter *****/
		psrc = select_subline(psrc, pdst);
		res = define_cmd_parser_parameter(pdst, &parser_line);
		
		/***** catch the argument ******/
		// TODO define_cmd_argument()
		
		switch (parser_line.cmd_idx)
		{
			case cmd_get_help:
				p_print("#################################################"NL
									"#                                               #"NL
									"#     ##   ## ######  ####  #####   #####       #"NL
									"#    //# #//   //   //     //  // //   //       #"NL
									"#   // # //   //   //     #####  //   //        #"NL
									"#  //   //   //   //     // #   //   //         #"NL
									"# //   // ######  ####  //   #  #####           #"NL
									"#                                               #"NL
									"#     #####   ####   #####   ##### ###### ##### #"NL
									"#    //  // //   // //  // //     //     //  // #"NL
									"#   #####  ####### #####   ####  ###### #####   #"NL
									"#  //     //   // // #       // //     // #     #"NL
									"# //     //   // //   # #####  ###### //   #    #"NL
									"#                                               #"NL
									"#################################################"NL
									NL
									"Structure of command: "NL
									"[command] [-p] [argument]"NL
									" -----------------------"NL
									"[command] - word of several signs (example: help, log, set, send...)"NL
									"[-p] - parameter of command, it contains an only sign (example: -p, -m... )"NL
									"[argument] - word of numeric or symbolic signs to specialize commands"NL
									);
				break;
			
			case cmd_get_list:
				p_print("list of commands"NL
									"1: help - general help"NL
									"2: list - get list of system"NL);
				break;
			
			default:
				p_print("unknown command!"NL);
				break;
		}
		
		p_print(NL">> ");
	}
}

