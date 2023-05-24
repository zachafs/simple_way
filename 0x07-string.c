#include "shell.h"

/**
 * lenGTH_str - returns the length of a string
 * @s: the string whose length to check
 *
 * Return: integer length of string
 */
int lenGTH_str(char *s)
{
	int length = 0;

	if (!s)
		return (0);

	while (*s++)
		length++;
	return (length);
}

/**
 * compar_str - performs lexicogarphic comparison of two strangs.
 * @s1: the first strang
 * @s2: the second strang
 *
 * Return: negative if s1 < s2, positive if s1 > s2, zero if s1 == s2
 */
int compar_str(char *s1, char *s2)
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
	else if (*s1 < *s2)
		return (-1);
		else
		return (1);

}

/**
 * starts_with - checks if needle starts with haystack
 * @haystack: string to search
 * @needle: the substring to find
 *
 * Return: address of next char of haystack or NULL
 */
char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle != *haystack)
			return (NULL);
		needle++;
		haystack++;
	return ((char *)haystack);
}

/**
 * concat_2str - concatenates two strings
 * @dest: the destination buffer
 * @src: the source buffer
 *
 * Return: pointer to destination buffer
 */
char *concat_2str(char *dest, char *src)
{
	char *ret = dest;

	for (; *dest; dest++)
		;
	for (; *src; src++, dest++)
		*dest = *src;
	*dest = *src;
	return (ret);
}
