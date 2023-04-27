#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#define BUFFER_SIZE 1024
#define MAX_ARGS 10

extern char **environ;

char *get_path(char *command)
{
	char *path = getenv("PATH");
	if (path == NULL)
	{
		return NULL;
	}

	char *dir = strtok(path, ":");
	while (dir != NULL)
	{
		char *fullpath = (char *)malloc(strlen(dir) + strlen(command) + 2);
		sprintf(fullpath, "%s/%s", dir, command);
		if (access(fullpath, X_OK) == 0)
		{
			return fullpath;
		}
		free(fullpath);
		dir = strtok(NULL, ":");
	}

	return NULL;
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

int main(void)
{
	char *buffer;
	size_t bufsize = BUFFER_SIZE;

	buffer = (char *)malloc(bufsize * sizeof(char));
	if (buffer == NULL)
	{
		perror("Error: malloc failed");
		exit(EXIT_FAILURE);
	}

	while (1)
	{
		printf("$ "); //Display prompt
		getline(&buffer, &bufsize, stdin); //Read command line
		// Remove trailing newline character
		buffer[strcspn(buffer, "\n")] = '\0';

		if (feof(stdin)) // Handle end of file condition
		{
			printf("\n");
			break;
		}

		if (strcmp(buffer, "exit") == 0) // Handle exit built-in
		{
			break;
		}

		if (strcmp(buffer, "env") == 0) // Handle env built-in
		{
			print_env();
			continue;
		}


		char *args[MAX_ARGS+1];
		char *token = strtok(buffer, " ");
		int i = 0;
		while (token != NULL && i < MAX_ARGS)
		{
			args[i] = token;
			token = strtok(NULL, " ");
			i++;
		}
		args[i] = NULL;

		char *command = args[0];
		char *path = get_path(command);
		if (path == NULL)
		{
			printf("Error: %s not found\n", command);
			continue;
		}

		pid_t pid = fork(); // Create child process
		if (pid < 0) // Handle error
		{
			perror("Error: fork failed");
			free(path); // added on task 3
			exit(EXIT_FAILURE);
		}
		else if (pid == 0) // Child process
		{
			int ret = execve(path, args, environ); // Execute command, buffer was replaced by args[0]; NULL by args and environ ommitted
			if (ret < 0) // Handle error
			{
				perror("Error: execve failed");
				free(path); // added on 3
				exit(EXIT_FAILURE);
			}
		}
		else // Parent process
		{
			int status;
			waitpid(pid, &status, 0); // Wait for child process to finish
		}

		free(path);
	}

	free(buffer);
	return 0;
}
