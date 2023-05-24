#include "shell.h"

/**
 **ncpy_str - copies a string
 *@dest: the destination string to be copied to
 *@src: the source string
 *@n: the amount of characters to be copied
 *Return: the concatenated string
 */
char *ncpy_str(char *dest, char *src, int n)
{
	int i;
	char *s = dest;

	for (i = 0; i < n - 1 && src[i] != '\0'; i++)
	{
		dest[i] = src[i];
		}
	for (; i < n; i++)
	{
		dest[i] = '\0';
	}

	return (s);
}

/**
 **ncat_str - concatenates two strings
 *@dest: the first string
 *@src: the second string
 *@n: the amount of bytes to be maximally used
 *Return: the concatenated string
 */
char *ncat_str(char *dest, char *src, int n)
{
	int i, j;
	char *s = dest;

	i = 0;
	j = 0;
	while (dest[i] != '\0')
		i++;
	for (j = 0; src[j] != '\0' && j < n; j++)
	{
		dest[i] = src[j];
		i++;
	}
	if (j < n)
		dest[i] = '\0';
	return (s);
}

/**
 **chr_str - locates a character in a string
 *@s: the string to be parsed
 *@c: the character to look for
 *Return: (s) a pointer to the memory area s
 */
char *chr_str(char *s, char c)
{
	while (*s != 0)
	{
		if (*s == c)
		return (s);
	s++;
	}

	return (NULL);
}
