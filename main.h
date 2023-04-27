#ifndef _MAIN_H_
#define _MAIN_H_
#include <stdlib.h>

#define BUFFER_SIZE 1024
#define MAX_ARGS 10

extern char **environ;
char *get_path(char *command);
void print_env(void);
char *buffer = (char *)malloc(bufsize * sizeof(char));
size_t bufsize = BUFFER_SIZE;
char *args[MAX_ARGS + 1];
char *token = strtok(buffer, " ");
char *command = args[0];
char *path = get_path(command);
args[i] = NULL;
int i = 0;
int ret = execve(path, args, environ);
pid_t pid = fork(); /* Create child process*/
int status;

#endif /* _MAIN_H_ */
