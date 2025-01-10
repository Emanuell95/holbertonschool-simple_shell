#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

extern char **environ; /* To access environment variables */

int main(void) {
    char *line = NULL;
    size_t len = 0;
    ssize_t nread;
    char *args[100];
    pid_t pid;

    while (1) {
        int i = 0;  /* Declare variables at the top */
        printf("simple_shell ");  /* Executable statement follows declarations */

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

        /* Built-in: exit */
        if (strcmp(args[0], "exit") == 0) {
            free(line);
            exit(0);
        }

        /* Built-in: cd */
        if (strcmp(args[0], "cd") == 0) {
            if (args[1] == NULL) {
                fprintf(stderr, "cd: expected argument\n");
            } else if (chdir(args[1]) != 0) {
                perror("cd");
            }
            continue; /* Avoid further processing */
        }

        /* Built-in: pwd */
        if (strcmp(args[0], "pwd") == 0) {
            char cwd[1024];
            if (getcwd(cwd, sizeof(cwd)) != NULL) {
                printf("%s\n", cwd);
            } else {
                perror("pwd");
            }
            continue; /* Avoid further processing */
        }

        /* Built-in: echo */
        if (strcmp(args[0], "echo") == 0) {
            int j = 1;
            for (; args[j] != NULL; j++) {
                printf("%s ", args[j]);
            }
            printf("\n");
            continue; /* Avoid further processing */
        }

        /* Built-in: env */
        if (strcmp(args[0], "env") == 0) {
            char **env = environ;
            for (; *env != NULL; env++) {
                printf("%s\n", *env);
            }
            continue; /* Avoid further processing */
        }

        /* Built-in: export */
        if (strcmp(args[0], "export") == 0) {
            if (args[1] == NULL || strchr(args[1], '=') == NULL) {
                fprintf(stderr, "export: usage: export VAR=value\n");
            } else {
                char *var = strtok(args[1], "=");
                char *value = strtok(NULL, "=");
                if (setenv(var, value, 1) != 0) {
                    perror("export");
                }
            }
            continue; /* Avoid further processing */
        }
        
           if (access(args[0], X_OK) != 0) {
           fprintf(stderr, "Command not found or not executable: %s\n", args[0]);
           continue; 
}
        /* Execute external commands */
        pid = fork();
        if (pid == 0) { /* Child process */
            if (execve(args[0], args, environ) == -1) {
                perror("./hsh");
            }
            exit(EXIT_FAILURE);
        } else if (pid < 0) {
            perror("fork");
        } else { /* Parent process */
            wait(NULL);
        }
    }

    free(line);  /* Free memory after loop ends */
    return 0;
}
