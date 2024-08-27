#include "shell.h"

int main(void)
{
    char *input;
    char **args;
    int status = 1;

    while (status)
    {
        _puts("$ ");  /* Custom prompt function */
        input = read_input();  /* Function to read user input */
        args = parse_input(input);  /* Parse the input into arguments */
        status = execute_command(args);  /* Execute the command */
        
        free(input);
        free(args);
    }

    return 0;
}

