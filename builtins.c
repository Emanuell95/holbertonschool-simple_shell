#include "shell.h"

/**
 * handle_builtins - Handles built-in commands like cd, pwd, echo, env, export, and exit.
 * @argv: Array of arguments.
 * Return: 0 if it's a built-in command, -1 otherwise.
 */
int handle_builtins(char **argv)
{
    /* Handle 'cd' command */
    if (_strcmp(argv[0], "cd") == 0)
    {
        if (argv[1] == NULL)  /* Check if argument for directory is missing */
            fprintf(stderr, "cd: expected argument\n");
        else if (chdir(argv[1]) != 0)  /* Change directory */
            perror("cd");
        return 0;
    }
    /* Handle 'pwd' command */
    else if (_strcmp(argv[0], "pwd") == 0)
    {
        char cwd[PATH_MAX];
        if (getcwd(cwd, sizeof(cwd)) != NULL)  /* Get current working directory */
            printf("%s\n", cwd);
        else
            perror("pwd");
        return 0;
    }
    /* Handle 'echo' command */
    else if (_strcmp(argv[0], "echo") == 0)
    {   
        int i = 1; 
        for (; argv[i] != NULL; i++)  /* Print arguments passed to echo */
        {
            printf("%s", argv[i]);
            if (argv[i + 1] != NULL)
                printf(" ");
        }
        printf("\n");
        return 0;
    }
    /* Handle 'env' command */
    else if (_strcmp(argv[0], "env") == 0)
    {   
        int i = 0;
        while (environ[i] != NULL)  /* Print all environment variables */
            printf("%s\n", environ[i++]);
        return 0;
    }
    /* Handle 'export' command */
    else if (_strcmp(argv[0], "export") == 0)
    {
        if (argv[1] != NULL)  /* Set environment variable */
        {
            putenv(argv[1]);
        }
        else
        {
            fprintf(stderr, "export: expected argument\n");  /* Print error if no argument */
        }
        return 0;
    }
    /* Handle 'exit' command */
    else if (_strcmp(argv[0], "exit") == 0)
    {
        return 1;  /* Indicate that the shell should exit */
    }

    return -1; /* Not a built-in command */
}

