#include "shell.h"

/**
 * handle_cd - Handles the 'cd' command.
 * @argv: Array of arguments passed to 'cd'.
 * Return: 0 on success, error code otherwise.
 */
int handle_cd(char **argv)
{
	if (argv[1] == NULL)
	{
		fprintf(stderr, "cd: expected argument\n");
		return (0);
	}
	if (chdir(argv[1]) != 0)
		perror("cd");
	return (0);
}

/**
 * handle_pwd - Handles the 'pwd' command.
 * Return: 0 on success, error code otherwise.
 */
int handle_pwd(void)
{
	char cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
		printf("%s\n", cwd);
	else
		perror("pwd");
	return (0);
}

/**
 * handle_echo_env_export - Handles the 'echo', 'env', and 'export' commands.
 * @argv: Array of arguments passed to the command.
 * Return: 0 on success, -1 if the command is not recognized.
 */
int handle_echo_env_export(char **argv)
{
	if (_strcmp(argv[0], "echo") == 0)
	{
		int i = 1;

		for (; argv[i] != NULL; i++)
		{
			printf("%s", argv[i]);
			if (argv[i + 1] != NULL)
				printf(" ");
		}
		printf("\n");
		return (0);
	}
	else if (_strcmp(argv[0], "env") == 0)
	{
		int i = 0;

		while (environ[i] != NULL)
			printf("%s\n", environ[i++]);
		return (0);
	}
	else if (_strcmp(argv[0], "export") == 0)
	{
		if (argv[1] != NULL)
			putenv(argv[1]);
		else
			fprintf(stderr, "export: expected argument\n");
		return (0);
	}
	return (-1);
}

/**
 * handle_builtins - Checks if a command is a built-in command and handles it.
 * @argv: Array of arguments passed to the command.
 * Return: 0 if it's a built-in command, 1 if it's 'exit', -1 otherwise.
 */
int handle_builtins(char **argv)
{
	if (_strcmp(argv[0], "cd") == 0)
		return (handle_cd(argv));
	else if (_strcmp(argv[0], "pwd") == 0)
		return (handle_pwd());
	else if (_strcmp(argv[0], "exit") == 0)
		return (1);

	return (handle_echo_env_export(argv));
}

