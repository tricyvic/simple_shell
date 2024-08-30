#include "shell.h"

/* Ensure environ is declared */
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
	int status;

	if (args[1] == NULL)
	{
		/* No status provided, exit with status 0 */
		exit(0);
	}
	else
	{
		status = atoi(args[1]);
		if (status == -1)
		{
			/* Print error if argument is not a valid integer */
			write(STDERR_FILENO, "exit: Illegal number: ", 22);
			write(STDERR_FILENO, args[1], strlen(args[1]));
			write(STDERR_FILENO, "\n", 1);
			return;
		}
		exit(status);
	}
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

/**
 * _atoi - converts a string to an integer
 * @s: string to convert
 * Return: integer value or -1 if conversion fails
 */
int _atoi(char *s)
{
	int result = 0;
	int i = 0;

	if (s[i] == '\0')
		return (-1);

	while (s[i] != '\0')
	{
		if (s[i] < '0' || s[i] > '9')
			return (-1);

		result = result * 10 + (s[i] - '0');
		i++;
	}
	return (result);
}

