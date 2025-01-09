#include "shell.h"

int main(void)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t nread;
    char *args[MAX_ARGS];
    pid_t pid;

    while (1) {
        int i = 0;
        printf("simple_shell ");  /* Prompt for input */

        nread = getline(&line, &len, stdin);
        if (nread == -1) {  /* End of input (Ctrl+D) */
            printf("\n");
            break;
        }

        line[nread - 1] = '\0';  /* Remove newline character */
        args[i] = strtok(line, " ");
        while (args[i] != NULL) {
            i++;
            args[i] = strtok(NULL, " ");
        }

        if (args[0] == NULL)
            continue;  /* Ignore empty input */

        /* Handle built-in commands */
        if (handle_builtins(args) == 1) {
            free(line);
            exit(0);  /* Exit the shell when 'exit' is called */
        }

        /* Execute external commands */
        pid = fork();
        if (pid == 0) {  /* Child process */
            char *command_path = get_path(args[0]);
            if (command_path != NULL) {
                if (execve(command_path, args, environ) == -1) {
                    perror("./hsh");
                }
            } else {
                fprintf(stderr, "Command not found: %s\n", args[0]);
            }
            exit(EXIT_FAILURE);
        } else if (pid < 0) {
            perror("fork");
        } else {  /* Parent process */
            wait(NULL);
        }
    }

    free(line);  /* Free memory after loop ends */
    return 0;
}

