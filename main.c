#include "shell.h"

/**
 * get_user_input - Prompts the user and reads the input.
 * @line: Pointer to the input line.
 * @args: Array to store the tokenized arguments.
 * Return: 0 if successful, -1 if end of input is reached.
 */
int get_user_input(char **line, char *args[MAX_ARGS])
{
	size_t len = 0;
	ssize_t nread;
	int i = 0;

	printf("simple_shell ");
	nread = getline(line, &len, stdin);
	if (nread == -1)
	{
		printf("\n");
		return (-1);
	}

	(*line)[nread - 1] = '\0';  /* Remove newline */
	args[i] = strtok(*line, " ");
	while (args[i] != NULL)
	{
		i++;
		args[i] = strtok(NULL, " ");
	}
	return (0);
}

/**
 * execute_builtin_command - Executes built-in commands.
 * @args: Array of arguments.
 * Return: 1 if 'exit' is called, 0 otherwise.
 */
int execute_builtin_command(char *args[MAX_ARGS])
{
	if (handle_builtins(args) == 1)
		return (1);
	return (0);
}

/**
 * create_process - Forks a process and executes external commands.
 * @args: Array of arguments.
 */
void create_process(char *args[MAX_ARGS])
{
	pid_t pid = fork();

	if (pid == 0)  /* Child process */
	{
		char *command_path = get_path(args[0]);

		if (command_path != NULL)
		{
			if (execve(command_path, args, environ) == -1)
				perror("./hsh");
		}
		else
		{
			fprintf(stderr, "Command not found: %s\n", args[0]);
		}
		exit(EXIT_FAILURE);
	}
	else if (pid < 0)  /* Error forking */
	{
		perror("fork");
	}
	else  /* Parent process */
	{
		wait(NULL);
	}
}

/**
 * main - Entry point of the shell program.
 * Return: 0 on success.
 */
int main(void)
{
	char *line = NULL;
	char *args[MAX_ARGS];

	while (1)
	{
		if (get_user_input(&line, args) == -1)
			break;

		if (args[0] == NULL)
			continue;

		if (execute_builtin_command(args) == 1)
		{
			free(line);
			exit(0);
		}

		create_process(args);
	}

	free(line);
	return (0);
}

