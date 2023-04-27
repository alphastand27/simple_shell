#include <stdio.h>
#include "main.h"

/**
 * get_path - gets path of argument
 * command - declared in main.h
 * print_env - prints environment of argument
 */
char *get_path(char *command)
{
	char *path = getenv("PATH");

	if (path == NULL)
	{
		return (NULL);
	}

	char *dir = strtok(path, ":");

	while (dir != NULL)
	{
		char *fullpath = (char *)malloc(strlen(dir) + strlen(command) + 2);

		sprintf(fullpath, "%s/%s", dir, command);
		if (access(fullpath, X_OK) == 0)
		{
			return (fullpath);
		}
		free(fullpath);
		dir = strtok(NULL, ":");
	}

	return (NULL);
}

void print_env(void)
{
	char **env = environ;

	while (*env != NULL)
	{
		printf("%s\n", *env);
		env++;
	}
}
