#include "shellmessages.h"
#include <stdio.h>

void writeWelcome()
{
	printf("Welcome to simple shell! Type \"exit\" to exit and \"?\" for help.\n");
}
void writeInvalidInput()
{
	fprintf(stderr,"Invalid input!\n");	
}
void writePromt(char *promt)
{
	printf("%s",promt);
}

void writeCommandNotFound(char* command)
{
	fprintf(stderr, "%s: command not found\n", command);
}
