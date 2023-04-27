#include <stdio.h>
#include <stdlib.h>

/**
 * main - entry point of program
 *
 * Return: Always 0
 */
int main(void)
{
	printf("PATH : %s\n", getenv("PATH"));
	printf("HOME : %s\n", getenv("HOME"));
	printf("ROOT : %s\n", getenv("ROOT"));
	return (0);
}
