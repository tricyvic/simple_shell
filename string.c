#include "shell.h"

/**
 * _strlen - Calculates the length of a string.
 * @s: The string whose length is to be determined.
 *
 * Return: The integer length of the string.
 */
int _strlen(char *s)
{
	int i = 0;

	if (!s)
		return (0);

	while (*s++)
		i++;
	return (i);
}

/**
 * _strcmp - Compares two strings lexicographically.
 * @s1: The first string to compare.
 * @s2: The second string to compare.
 *
 * Return: A negative value if `s1` is less than `s2`,
 *         a positive value if `s1` is greater than `s2`,
 *         zero if `s1` is equal to `s2`.
 */
int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}

/**
 * starts_with - Checks if a string (needle) starts with a given prefix (haystack).
 * @haystack: The string to search within.
 * @needle: The substring to find at the beginning of `haystack`.
 *
 * Return: Pointer to the character in `haystack` immediately following `needle`,
 *         or NULL if `needle` is not found at the start of `haystack`.
 */
char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * _strcat - Concatenates two strings.
 * @dest: The destination buffer to which `src` will be appended.
 * @src: The source buffer to be appended to `dest`.
 *
 * Return: Pointer to the destination buffer (`dest`).
 */
char *_strcat(char *dest, char *src)
{
	char *ret = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (ret);
}

