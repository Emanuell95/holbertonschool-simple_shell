#include "shell.h"

/**
 * get_path - Get the full path of a command
 * from the PATH environment variable.
 * @command: The command to search for in the PATH directories.
 *
 * Return: The full path of the command if found, NULL otherwise.
 */
char *get_path(const char *command)
{
	char *path_env;
	char *path_copy;
	char *dir;
	char *full_path;

	path_env = getenv("PATH");
	if (path_env == NULL)
		return (NULL);

	path_copy = strdup(path_env);
	if (path_copy == NULL)
		return (NULL);

	dir = strtok(path_copy, ":");
	while (dir != NULL)
	{
		full_path = malloc(strlen(dir) + strlen(command) + 2);
		if (full_path == NULL)
		{
			free(path_copy);
			return (NULL);
		}

		snprintf(full_path, strlen(dir) + strlen(command) + 2,
			 "%s/%s", dir, command);
		if (access(full_path, X_OK) == 0)
		{
			free(path_copy);
			return (full_path);
		}
		free(full_path);

		dir = strtok(NULL, ":");
	}

	free(path_copy);
	return (NULL);
}

