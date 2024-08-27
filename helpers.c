#include "shell.h"

/**
 * split_string - tokenizes a string into an array of strings
 * @input: string to split
 * @delim: delimiters for tokenizing
 * Return: pointer to array of strings
 */
char **split_string(char *input, const char *delim)
{
	char **tokens = NULL;
	char *token;
	int i = 0;
	size_t bufsize = 64;

	tokens = malloc(bufsize * sizeof(char *));
	if (!tokens)
		return (NULL);

	token = strtok(input, delim);
	while (token)
	{
		tokens[i++] = strdup(token);
		if (i >= (int)bufsize)
		{
			bufsize += 64;
			tokens = realloc(tokens, bufsize * sizeof(char *));
			if (!tokens)
				return (NULL);
		}
		token = strtok(NULL, delim);
	}
	tokens[i] = NULL;
	return (tokens);
}

/**
 * execute_command - forks and executes a command
 * @args: command and its arguments
 */
void execute_command(char **args)
{
	pid_t pid = fork();

	if (pid == 0)
	{
		if (execvp(args[0], args) == -1)
		{
			perror("hsh");
		}
		exit(EXIT_FAILURE);
	}
	else if (pid < 0)
	{
		perror("hsh");
	}
	else
	{
		wait(NULL);
	}
}

/**
 * free_args - frees an array of strings
 * @args: array of strings
 */
void free_args(char **args)
{
	int i;

	for (i = 0; args[i]; i++)
	{
		free(args[i]);
	}
	free(args);
}

