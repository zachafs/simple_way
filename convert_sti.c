#include "shell.h"

/**
 * is_active - returns true if shell is interactive mode
 * @strct: struct address
 *
 * Return: 1 if interactive mode, 0 otherwise
 */
int is_active(struc_t *strct)
{
	return (isatty(STDIN_FILENO) && strct->readfd <= 2);
}

/**
 * is_delim - checks if character is a delimeter
 * @c: the char to check
 * @delim: the delimeter string
 * Return: 1 if true, 0 if false
 */
int is_delim(char c, char *delim)
{
	for (; *delim; delim++)
	{
		if (*delim++ == c)
		return (1);
	}
		return (0);
}

/**
 * is_alpha - checks for alphabetic character
 * @c: The character to input
 * Return: 1 if c is alphabetic, 0 otherwise
 */

int is_alpha(int c)
{
	while ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
	{
		return (1);
	}
		return (0);
}
/**
 * convert_sti - converts a string to an integer
 * @s: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 */

int convert_sti(char *s)
{
	int i, sign = 1, flag = 0;
	unsigned int result = 0;

	for (i = 0; s[i] != '\0' && flag != 2; i++)
	{
		if (s[i] == '-')
			sign *= -1;

		if (s[i] >= '0' && s[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}
	int output = (sign == -1) ? -result : result;

	return (output);
}
