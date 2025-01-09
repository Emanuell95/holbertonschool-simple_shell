#include "shell.h"

void execute_command(char *line)
{
    char *args[MAX_ARGS];
    int i = 0;
    pid_t pid;
    char *command_path;

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

    /* Handle built-in commands first */
    if (handle_builtins(args) == 1)
        return;

    /* Get the full path of the command using get_path */
    command_path = get_path(args[0]);
    if (command_path == NULL)
    {
        fprintf(stderr, "%s: command not found\n", args[0]);
        return;  /* Command not found */
    }

    /* Fork a child process to execute the command */
    pid = fork();
    if (pid == 0)  /* Child process */
    {
        if (execve(command_path, args, environ) == -1)
        {
            perror("execve failed");
            exit(EXIT_FAILURE);
        }
    }
    else if (pid < 0)  /* Fork failed */
    {
        perror("fork");
    }
    else  /* Parent process */
    {
        wait(NULL);  /* Wait for the child process to finish */
    }

    free(command_path);  /* Free the memory allocated for the command path */
}

