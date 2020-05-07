#ifndef PARSER_H
#define PARSER_H

#include "main.h"
#include "math.h"

#define ALL_COMMANDS    3
#define ALL_PARAMETERS  2

typedef enum
{
	cmd_unknown		= 0,
	cmd_get_help	= 1,
	cmd_get_log		= 2
} cmd_idx_type;

typedef enum
{
	prm_unknown			= 0,
	prm_first_param	= 1
} cmd_prm_type;

typedef struct _parser_struct 
{
    unsigned char		cmd_idx_name[256];
    cmd_idx_type		cmd_idx;
    cmd_prm_type		cmd_prm[8];
    unsigned int		int_argument[2];
    unsigned char		chr_argument[512];
} parser_struct;

void prs_copy_to_start_line(unsigned char* extern_line);
void print_cmd_parser_struct(parser_struct *parser_print);
cmd_idx_type define_cmd_parser_index(unsigned char *cmd_line);

void parser_routine(char *status);

#endif

