#include "shell.h"

/**
 * _memset - Fills a block of memory with a constant byte.
 * @s: Pointer to the memory area to be filled.
 * @b: The byte value to set in the memory area.
 * @n: The number of bytes to set.
 *
 * Return: Pointer to the memory area `s`.
 */
char *_memset(char *s, char b, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		s[i] = b;
	return (s);
}

/**
 * ffree - Frees a string of strings.
 * @pp: Pointer to the array of strings (each string should be freed).
 *
 * Return: Void.
 */
void ffree(char **pp)
{
	char **a = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(a);
}

/**
 * _realloc - Reallocates a block of memory.
 * @ptr: Pointer to the previously allocated memory block.
 * @old_size: The byte size of the previous memory block.
 * @new_size: The byte size of the new memory block.
 *
 * Return: Pointer to the newly allocated memory block.
 *         If `new_size` is zero, and `ptr` is not NULL, the old block is freed and NULL is returned.
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *p;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	p = malloc(new_size);
	if (!p)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		p[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (p);
}

