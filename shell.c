#include "shell.h"

/**
 * signal_handler - handles Ctrl+C
 * @sig_num: signal number
 */
void signal_handler(int sig_num)
{
	if (sig_num == SIGINT)
	{
		write(STDOUT_FILENO, "\n$ ", 3);
	}
}

/**
 * check_EOF - handles EOF (Ctrl+D)
 * @len: length of getline
 * @input: user input buffer
 */
void check_EOF(ssize_t len, char *input)
{
	if (len == -1)
	{
		if (isatty(STDIN_FILENO))
		{
			write(STDOUT_FILENO, "\n", 1);
		}
		free(input);
		exit(0);
	}
}

/**
 * prompt_display - displays the shell prompt
 */
void prompt_display(void)
{
	if (isatty(STDIN_FILENO))
		write(STDOUT_FILENO, "$ ", 2);
}

/**
 * main - entry point for the shell
 * Return: 0 on success, otherwise error code
 */
int main(void)
{
	char *input = NULL, **args;
	size_t bufsize = 0;
	ssize_t len;
	list_path *path_list = NULL;
	void (*builtin_func)(char **);

	signal(SIGINT, signal_handler);

	while (1)
	{
		prompt_display();
		len = getline(&input, &bufsize, stdin);
		check_EOF(len, input);

		args = split_string(input, " \n");
		if (args && args[0])
		{
			builtin_func = check_builtin(args);
			if (builtin_func)
			{
				builtin_func(args);
			}
			else
			{
				char *path = locate_executable(args[0], &path_list);
				if (path)
				{
					free(args[0]);
					args[0] = path;
				}
				execute_command(args);
			}
		}
		free_args(args);
	}
	free(input);
	free_path_list(path_list);
	return (0);
}

