#include "shell.h"

extern char **environ;
/**
 * check_builtin - checks for built-in commands
 * @args: command and arguments
 * Return: function pointer to built-in command or NULL if not found
 */
void (*check_builtin(char **args))(char **)
{
	if (strcmp(args[0], "exit") == 0)
		return (builtin_exit);
	if (strcmp(args[0], "env") == 0)
		return (builtin_env);
	return (NULL);
}

/**
 * builtin_exit - exits the shell
 * @args: command and arguments
 */
void builtin_exit(char **args)
{
	UNUSED(args);
	exit(0);
}

/**
 * builtin_env - prints the environment variables
 * @args: command and arguments
 */
void builtin_env(char **args)
{
	int i;

	UNUSED(args);
	for (i = 0; environ[i]; i++)
	{
		write(STDOUT_FILENO, environ[i], strlen(environ[i]));
		write(STDOUT_FILENO, "\n", 1);
	}
}

