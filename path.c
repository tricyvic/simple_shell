#include "shell.h"

/**
 * build_path_list - creates a linked list of directories from PATH
 * @path: string containing the PATH
 * Return: pointer to head of the list
 */
list_path *build_path_list(char *path)
{
	list_path *head = NULL, *new_node, *temp;
	char *token = strtok(path, ":");

	while (token)
	{
		new_node = malloc(sizeof(list_path));
		if (!new_node)
			return (NULL);
		new_node->directory = strdup(token);
		new_node->next = NULL;

		if (!head)
			head = new_node;
		else
		{
			temp = head;
			while (temp->next)
				temp = temp->next;
			temp->next = new_node;
		}
		token = strtok(NULL, ":");
	}
	return (head);
}

/**
 * locate_executable - finds the full path of a command
 * @cmd: command name
 * @path_list: pointer to the linked list of directories
 * Return: full path to executable or NULL if not found
 */
char *locate_executable(char *cmd, list_path **path_list)
{
	struct stat st;
	list_path *temp;
	char *full_path;

	if (stat(cmd, &st) == 0)
		return (strdup(cmd));

	if (!*path_list)
		*path_list = build_path_list(getenv("PATH"));

	temp = *path_list;
	while (temp)
	{
		full_path = malloc(strlen(temp->directory) + strlen(cmd) + 2);
		if (!full_path)
			return (NULL);
		sprintf(full_path, "%s/%s", temp->directory, cmd);
		if (stat(full_path, &st) == 0)
			return (full_path);

		free(full_path);
		temp = temp->next;
	}
	return (NULL);
}

/**
 * free_path_list - frees the linked list of PATH directories
 * @head: head of the list
 */
void free_path_list(list_path *head)
{
	list_path *temp;

	while (head)
	{
		temp = head;
		head = head->next;
		free(temp->directory);
		free(temp);
	}
}

