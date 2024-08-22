#include "shell.h"

/**
 * main - Entry point for the shell
 * Return: Always 0 (Success)
 */
int main(void)
{
    char *line = NULL;
    size_t len = 0;
    int status = 1;

    while (status)
    {
        if (isatty(STDIN_FILENO))
            write(STDOUT_FILENO, "$ ", 2);


        if (getline(&line, &len, stdin) == -1)
        {
            free(line);
            exit(EXIT_FAILURE);
        }

    }

    free(line);
    return (0);
}

