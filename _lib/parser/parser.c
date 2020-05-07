#include "parser.h"
#include "parser_io.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

parser_struct parser_line;

unsigned char cmd_idx_names[ALL_COMMANDS][16] = 
{
	"unknown",
	"help",
	"log"
};

unsigned char cmd_parser_prm_name[ALL_PARAMETERS][10] = 
{ 
	"!"       // single argument
};

unsigned char start_line[256];

void prs_copy_to_start_line(unsigned char *extern_line)
{
	int i;
	for (i = 0; i < 255; i++)
		start_line[i] = *extern_line++;
}

void print_cmd_parser_struct(parser_struct *parser_print)
{
	//uint8_t i;
	prs_print("\n\r""command description:");
	prs_print("\n\rname: \t");
	prs_print(parser_print->cmd_idx_name);
	prs_print("\n\rindex: \t");
	prs_print_int(parser_print->cmd_idx);/*
	for (i = 0; i < 8; i++) 
	{
		if (parser_print->cmd_prm[i] == -1) break;
		printf("\nparam(%d): \t%d", i, parser_print->cmd_prm[i]);
	}
	printf("\nint_arg: \t%d", parser_print->int_argument[0]);
	printf("\nint_arg: \t%d", parser_print->int_argument[1]);
	printf("\nchr_arg: \t%s\n", parser_print->chr_argument);*/
}

cmd_idx_type define_cmd_parser_index(unsigned char *cmd_line)
{
	int i, j, k = 0;
	unsigned char *p = cmd_line, *pp, c1, c2;
	unsigned int numbers[ALL_COMMANDS];

	for (i = 0; i < ALL_COMMANDS; i++) 
	{
		if ((strstr((const char *)start_line, (const char *)cmd_idx_names[i]) != NULL) && 
				(strcmp((const char *)start_line, (const char *)cmd_idx_names[i]) == 0)) 
		{
			return ((cmd_idx_type) i);
		}
	}
	return cmd_unknown;	
}

void parser_routine(char *status)
{
	if (*status != 0)
	{
		*status = 0;
		parser_line.cmd_idx = define_cmd_parser_index(start_line);
		
		// command action START
		
		switch (parser_line.cmd_idx)
		{
			case cmd_get_help:
				prs_print("--- help ---"NL
									"list of commands"NL
									"1: help - general command list"NL
									"2: log  - get log of system"NL);
				break;
			
			case cmd_get_log:
				prs_print("    #   # #####  #### ####   ### "NL
									"   /# #/   /   /     /   / /   /"NL
									"  / # /   /   /     ####  /   /"NL
									" /   /   /   /     / #   /   /"NL
									"/   / #####  #### /   #  ### "NL
									NL
									"    ####   ###  ####   #### ##### #### "NL
									"   /   / /   / /   / /     /     /   /"NL
									"  ####  ##### ####   ###  ##### #### "NL
									" /     /   / / #       / /     / #  "NL
									"/     /   / /   # ####  ##### /   #"NL
									NL
									"tiny parser for microcontroller"NL
									);
				break;
			
			default:
				prs_print("unknown command!"NL);
				break;
		}
		
		// command action END
		
		prs_print(NL">> ");
	}
}

