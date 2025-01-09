#include "shell.h"

/* Function to get the full path of a command */
char *get_path(const char *command)
{
    char *path_env;
    char *path_copy;
    char *dir;
    char *full_path;

    path_env = getenv("PATH");  /* Get the PATH environment variable */
    if (path_env == NULL)
        return NULL;  /* If PATH is not set, return NULL */

    path_copy = strdup(path_env);  /* Duplicate PATH string to tokenize */
    if (path_copy == NULL)
        return NULL;  /* If strdup fails, return NULL */

    dir = strtok(path_copy, ":");  /* Tokenize PATH using ':' as the delimiter */
    while (dir != NULL)
    {
        full_path = malloc(strlen(dir) + strlen(command) + 2);  /* Allocate memory for full path */
        if (full_path == NULL)
        {
            free(path_copy);  /* Free path_copy before returning NULL */
            return NULL;
        }

        sprintf(full_path, "%s/%s", dir, command);  /* Concatenate the directory and command */
        if (access(full_path, X_OK) == 0)  /* Check if the file is executable */
        {
            free(path_copy);  /* Free path_copy before returning full_path */
            return full_path;
        }
        free(full_path);  /* Free full_path if command is not found in this directory */

        dir = strtok(NULL, ":");  /* Get the next directory in PATH */
    }

    free(path_copy);  /* Free path_copy before returning NULL */
    return NULL;  /* Command not found in any directory */
}

