#include "shell.h"

void execute_command(char *line)
{
    char *args[MAX_ARGS];
    int i = 0;
    pid_t pid;

    /* Parse the input line into arguments */
    args[i] = strtok(line, " ");
    while (args[i] != NULL && i < MAX_ARGS - 1)
    {
        i++;
        args[i] = strtok(NULL, " ");
    }
    args[i] = NULL; /* Null-terminate the arguments array */

    if (args[0] == NULL)
        return; /* No command entered */

    /* Fork a child process to execute the command */
    pid = fork();
    if (pid == 0) /* Child process */
    {
        if (execve(args[0], args, environ) == -1)
        {
            perror("./hsh");
            exit(EXIT_FAILURE);
        }
    }
    else if (pid < 0) /* Fork failed */
    {
        perror("fork");
    }
    else /* Parent process */
    {
        wait(NULL); /* Wait for the child process to finish */
    }
}
