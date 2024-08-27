#include "shell.h"

char *read_input(void)
{
    char *line = NULL;
    size_t bufsize = 0;

    if (getline(&line, &bufsize, stdin) == -1)
    {
        if (feof(stdin))  /* Handle EOF */
            exit(EXIT_SUCCESS);
        else
            perror("getline");
    }

    return line;
}

