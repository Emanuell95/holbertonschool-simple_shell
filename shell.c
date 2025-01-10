#include "shell.h"

/**
 * parse_args - Parse the input line into arguments.
 * @line: The input command line.
 * @args: The array to store the parsed arguments.
 *
 * Return: The number of arguments parsed.
 */
int parse_args(char *line, char *args[])
{
	int i = 0;

	args[i] = strtok(line, " ");
	while (args[i] != NULL && i < MAX_ARGS - 1)
	{
		i++;
		args[i] = strtok(NULL, " ");
	}
	args[i] = NULL;

<<<<<<< HEAD
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
=======
	return (i);
>>>>>>> 6f5a319e34d2ca544110c4391f756993197440ca
}

/**
 * execute_builtin - Handle built-in commands.
 * @args: The array of arguments.
 *
 * Return: 1 if the command is a built-in, 0 otherwise.
 */
int execute_builtin(char *args[])
{
	if (handle_builtins(args) == 1)
		return (1);
	return (0);
}

/**
 * fork_and_execute - Fork a child process to execute an external command.
 * @command_path: The full path of the command.
 * @args: The arguments for the command.
 */
void fork_and_execute(char *command_path, char *args[])
{
	pid_t pid;

	pid = fork();
	if (pid == 0)
	{
		if (execve(command_path, args, environ) == -1)
		{
			perror("execve failed");
			exit(EXIT_FAILURE);
		}
	}
	else if (pid < 0)
	{
		perror("fork");
	}
	else
	{
		wait(NULL);
	}
}

/**
 * execute_command - Main function to execute the command line input.
 * @line: The input line with the command and arguments.
 */
void execute_command(char *line)
{
	char *args[MAX_ARGS];
	int i;
	char *command_path;

	i = parse_args(line, args);
	if (i == 0)
		return;

	if (execute_builtin(args))
		return;

	command_path = get_path(args[0]);
	if (command_path == NULL)
	{
		fprintf(stderr, "%s: command not found\n", args[0]);
		return;
	}

	fork_and_execute(command_path, args);

	free(command_path);
}

