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
	cmd_get_list	= 2
	//add new command
} cmd_idx_type;

typedef enum
{
	prm_unknown			= 0,
	prm_first_param	= 1
	// add new param
} cmd_prm_type;

typedef struct _parser_struct 
{
    unsigned char		cmd_idx_name[256];
    cmd_idx_type		cmd_idx;
    cmd_prm_type		cmd_prm;
    unsigned int		int_argument[2];
    unsigned char		chr_argument[512];
} parser_struct;

void prs_copy_to_start_line(unsigned char* extern_line);
void parser_routine(char *status);

#endif

