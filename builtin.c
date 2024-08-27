#include "shell.h"
#include <unistd.h>

/**
 * cd_command - Built-in function to change the directory.
 * @args: Array of command arguments.
 *
 * Return: 1 on success, or -1 on failure.
 */
int cd_command(char **args)
{
    char *dir;
    char cwd[1024];
    static char oldpwd[1024]; /* Store the previous working directory */

    /* Handle the case where no argument is provided (cd with no args) */
    if (args[1] == NULL)
    {
        dir = getenv("HOME"); /* Get the home directory */
        if (dir == NULL)
        {
            perror("cd: HOME not set");
            return -1;
        }
    }
    else if (strcmp(args[1], "-") == 0)
    {
        /* Handle the 'cd -' case (go to the previous directory) */
        if (strlen(oldpwd) == 0)
        {
            perror("cd: OLDPWD not set");
            return -1;
        }
        dir = oldpwd;
        _puts(oldpwd);
        _puts("\n");
    }
    else
    {
        /* Directory provided by the user */
        dir = args[1];
    }

    /* Get the current working directory before changing it */
    if (getcwd(cwd, sizeof(cwd)) == NULL)
    {
        perror("getcwd");
        return -1;
    }

    /* Change the directory */
    if (chdir(dir) != 0)
    {
        perror("cd");
        return -1;
    }

    /* Update the OLDPWD environment variable */
    if (setenv("OLDPWD", cwd, 1) != 0)
    {
        perror("setenv");
        return -1;
    }

    /* Get the new current working directory after the change */
    if (getcwd(cwd, sizeof(cwd)) == NULL)
    {
        perror("getcwd");
        return -1;
    }

    /* Update the PWD environment variable */
    if (setenv("PWD", cwd, 1) != 0)
    {
        perror("setenv");
        return -1;
    }

    /* Store the old working directory for 'cd -' */
    strcpy(oldpwd, cwd);

    return 1;
}

/**
 * builtin_command - Handles built-in commands like cd and exit.
 * @args: Command and its arguments.
 *
 * Return: 1 if a built-in command was executed, 0 otherwise.
 */
int builtin_command(char **args)
{
    if (strcmp(args[0], "cd") == 0)
    {
        return cd_command(args);
    }

    if (strcmp(args[0], "exit") == 0)
    {
        exit(0);
    }

    return 0;
}

