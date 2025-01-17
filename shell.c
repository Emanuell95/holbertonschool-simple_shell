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

	return (i);
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
