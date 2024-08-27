#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <errno.h>

char *read_input(void);
char **parse_input(char *input);
int execute_command(char **args);
int builtin_command(char **args);
void _puts(char *str);


#define TOK_BUFSIZE 64
#define TOK_DELIM " \t\r\n\a"

#endif

