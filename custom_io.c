#include "shell.h"

void _puts(char *str)
{
    write(STDOUT_FILENO, str, strlen(str));
}

