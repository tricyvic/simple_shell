#include "shell.h"
#include <sys/stat.h>

extern char **environ;

char *find_command_in_path(char *command);

int execute_command(char **args)
{
    pid_t pid;
    int status;
    char *command_path;

    if (args[0] == NULL)  /* Empty command */
        return 1;

    /* Find the command in PATH */
    command_path = find_command_in_path(args[0]);
    if (command_path == NULL)
    {
        /* Command not found */
        _puts(args[0]);
        _puts(": command not found\n");
        return 1;
    }

    /* Fork and execute only if the command is found */
    pid = fork();
    if (pid == 0)
    {
        /* Child process: execute the command */
        if (execve(command_path, args, environ) == -1)
        {
            perror("execve");
        }
        exit(EXIT_FAILURE);
    }
    else if (pid < 0)
    {
        /* Fork failed */
        perror("fork");
    }
    else
    {
        /* Parent process: wait for the child to finish */
        do {
            waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }

    /* Free the dynamically allocated command path if necessary */
    if (command_path != args[0])
        free(command_path);

    return 1;
}

char *find_command_in_path(char *command)
{
    char *path, *path_copy, *dir;
    char full_path[1024];
    struct stat sb;

    /* Check if the command is an absolute or relative path */
    if (stat(command, &sb) == 0 && (sb.st_mode & S_IXUSR))
    {
        return command;
    }

    /* Get the PATH environment variable */
    path = getenv("PATH");
    if (path == NULL)
        return NULL;

    /* Duplicate the PATH string */
    path_copy = strdup(path);
    if (path_copy == NULL)
    {
        perror("strdup");
        exit(EXIT_FAILURE);
    }

    /* Split the PATH into individual directories */
    dir = strtok(path_copy, ":");
    while (dir != NULL)
    {
        /* Construct the full path to the command */
        snprintf(full_path, sizeof(full_path), "%s/%s", dir, command);

        /* Check if the command exists and is executable */
        if (stat(full_path, &sb) == 0 && (sb.st_mode & S_IXUSR))
        {
            free(path_copy);
            return strdup(full_path);  /* Return a copy of the full path */
        }

        dir = strtok(NULL, ":");
    }

    /* Command not found in any PATH directory */
    free(path_copy);
    return NULL;
}

