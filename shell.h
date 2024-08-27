#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <errno.h>
#include <signal.h>
#include <sys/stat.h>
#include <sys/types.h>

#define UNUSED(x) (void)(x)

/* Function Prototypes */
void signal_handler(int sig_num);
void check_EOF(ssize_t len, char *input);
void prompt_display(void);
void execute_command(char **args);
void free_args(char **args);

/* String Helpers */
char **split_string(char *input, const char *delim);

/* Path Linked List */
typedef struct path_node
{
	char *directory;
	struct path_node *next;
} list_path;

char *locate_executable(char *cmd, list_path **path_list);
list_path *build_path_list(char *path);
void free_path_list(list_path *head);

/* Built-in Commands */
void (*check_builtin(char **args))(char **);
void builtin_exit(char **args);
void builtin_env(char **args);

#endif

