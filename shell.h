#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <limits.h>
#define MAX_ARGS 64

extern char **environ;

/* Function Prototypes */
int handle_builtins(char **argv);
int _strcmp(const char *s1, const char *s2);
char *get_path(const char *command);
void execute_command(char *line);

#endif
