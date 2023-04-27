#include <stdio.h>

/**
 * main - a program that prints its name, followed by a new line
 * @av: argument value, a strings that come after calling function
 * Return: Always 0 (Success)
 */
int main(char *av[])
{
	while (*av)
		printf("%s\n", *av++);
	return (0);
}
