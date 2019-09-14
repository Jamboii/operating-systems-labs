/*
    Alex Benasutti
    CSC345-01
    Lab 02 Exercise 1
*/

#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <wait.h>

int value = 5;
int main()
{
	pid_t pid;
	pid = fork();
	if (pid == 0) // CHILD PROCESS
	{
		value += 15;
		return 0;
	}
	else if (pid > 0) // PARENT PROCESS
	{
		wait(NULL);
		printf("PARENT: value = %d\n",value); // LINE A - output will be initial 'value'
		return 0;
	}
	return 0;
}
