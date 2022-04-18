#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

#include "shellmessages.h"

char promt[]= "myshell> ";
#define MAX_LENGTHS 128
#define MAX_ARGS 16
char *programs[] = {"ls","ps","cal"};
int exitstatus;

int main(int argc, char **argv)
{
	char input[MAX_LENGTHS];
	int program;
	writeWelcome();
	
	Input_start:
	writePromt(promt);
	
	if(fgets(input, MAX_LENGTHS, stdin)==NULL)
	{
		fprintf(stderr,"Cant Read stdin\n");
		return 1;
	}
	if((strlen(input)!=2) || ((input[0]<'1')||(input[0]>'4')))//checks if length is 2 and the char is a number
	{
		writeInvalidInput();
		goto Input_start;
	}
	if(input[0]=='4')
	{
		exit(0);
	}
	program=input[0]-'1';
	
	char tempargs[MAX_LENGTHS];
	printf("You can add up to %d arguments. Leave blank or enter \"no\" to execute without any arguments\n",MAX_ARGS);
	if(fgets(tempargs, MAX_LENGTHS-20, stdin)==NULL)
	{
		fprintf(stderr,"Cant Read stdin\n");
		return 1;
	}
	if(strcmp(tempargs, "no\n")==0)
	{
		tempargs[0]=0;
	}
	char *args[MAX_ARGS];
	char **next=args;

	char targs[MAX_LENGTHS];
	strcpy(targs, programs[program]);
	strcat(targs, " ");
	strcat(targs,tempargs);
	
	char *temp =strtok(targs, " \n");
	while (temp!=NULL)
	{
		*next++=temp;
		temp = strtok(NULL, " \n");
	}
	*next =NULL;
	
	int pid=fork();
	if(pid==-1)
	{
		return 76;
	}
	if (pid==0)
	{
		int err = execvp(args[0], args);
		if(err==-1)
		{
			fprintf(stderr, "%s: command not found\n", args[0]);
		}
	}
	int status;
	wait(&status);
	if(WIFEXITED(status))
	{
		exitstatus = WEXITSTATUS(status);
		printf("Exitcode: %d\n", exitstatus);
	}
	
	goto Input_start;
	return 0;
}

