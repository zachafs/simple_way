#include "shell.h"

/**
 * **splits_strtow - splits a string into words. Repeat delimiters are ignored
 * @str: the input string
 * @delim: the delimeter string
 * Return: a pointer to an array of strings, or NULL on failure
 */

char **splits_strtow(char *str, char *delim)
{
	int i, j, z, m, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!delim)
		delim = " ";
	for (i = 0; str[i] != '\0'; i++)
		if (!is_delim(str[i], delim) && (is_delim(str[i + 1], delim) || !str[i + 1]))
			numwords++;

	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < numwords; j++)
	{
		while (is_delim(str[i], delim))
			i++;
		z = 0;
		while (!is_delim(str[i + z], delim) && str[i + z])
			z++;
		s[j] = malloc((z + 1) * sizeof(char));
		if (!s[j])
		{
			for (z = 0; z < j; z++)
				free(s[z]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < z; m++)
			s[j][m] = str[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}

/**
 * **splits_strtow2 - splits a string into words
 * @str: the input string
 * @delim: the delimeter
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **splits_strtow2(char *str, char delim)
{
	int i, j, z, m, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (i = 0; str[i] != '\0'; i++)
		if ((str[i] != delim && str[i + 1] == delim) ||
				    (str[i] != delim && !str[i + 1]) || str[i + 1] == delim)
			numwords++;
	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < numwords; j++)
	{
		while (str[i] == delim && str[i] != delim)
			i++;
		z = 0;
		while (str[i + z] != delim && str[i + z] && str[i + z] != delim)
			z++;
		s[j] = malloc((z + 1) * sizeof(char));
		if (!s[j])
		{
			for (z = 0; z < j; z++)
				free(s[z]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < z; m++)
			s[j][m] = str[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}
