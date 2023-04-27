#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * main - entry point of the program
 * @ac: int
 * @av: character
 *
 * Return: Always 0
 */
int main(int ac, char **av[])
{
	DIR *dp = opendir(av[1]);
	struct dirent *dentry;

	if (!(dp))
	{
		printf("opendir error\n");
		exit(2);
	}

	while (1)
	{
		dentry = readdir(dp);
		if (!dentry)
			break;

		printf("%s\n", dentry->d_name);
	}
	return (0);
}
