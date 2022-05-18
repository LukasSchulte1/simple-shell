#include "inputprocessing.h"

#include "shellmessages.h"
#include <stdio.h>
#include <string.h>

int create_exec_arg_arr(char **next, char* temp_tok)
{
	while (temp_tok!=NULL)
	{
 		*next++=temp_tok;
		temp_tok = strtok(NULL, " \n");
	}
	*next =NULL;
	return 0;
}

int check_syntax(char *input)
{
	//To Do
	return 0;
}


void process_input(char **args, char *input)
{
	if (check_syntax(input))
	{
		writeInvalidInput();
		return;
	}

	char **next=args;
	char *temp_tok = strtok(input, " \n");
	create_exec_arg_arr(next, temp_tok);
}

