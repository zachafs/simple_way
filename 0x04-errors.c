#include "shell.h"

/**
 * err_convert - converts a string to an integer
 * @s: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 *       -1 on error
 */
int err_convert(char *s)
{
	unsigned long int result = 0;

	if (*s == '+')
		s++;
	while (*s != 0)
	{
		if (*s >= '0' && *s <= '9')
		{
			result *= 10 + (*s - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
		{
			return (-1);
		}
		s++;
	}
	return (result);
}

/**
 * msg_error - prints an error message
 * @strct: the parameter & return info struct
 * @estr: string containing specified error type
 * Return: 0 if no numbers in string, converted number otherwise
 *        -1 on error
 */
void msg_error(struc_t *strct, char *estr)
{
	_eputs(strct->fname);
	_eputs(": ");
	print_modulo(strct->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(strct->argv[0]);
	_eputs(": ");
	_eputs(estr);
}

/**
 * print_modulo - function prints a decimal (integer) number (base 10)
 * @input: the input
 * @fd: the filedescriptor to write to
 *
 * Return: number of characters printed
 */
int print_modulo(int input, int fd)
{
	int (*__putchar)(char) =
	(fd == STDERR_FILENO) ? _eputchar : _putchar;
	int count = 0;
	unsigned int _abs_, current;

	if (input < 0)
	{
		_abs_ = -input;
		count += __putchar('-');
	}
	else
		_abs_ = input;
		current = _abs_;

	if (current == 0)
	count += __putchar('0');

	while (current > 0)
	{
		int digit = current % 10;

		count += __putchar('0' + digit);
		current /= 10;
		}

	return (count);
}

/**
 * convert_num - converter function, a clone of itoa
 * @num: number
 * @base: base
 * @flags: argument flags
 *
 * Return: string
 */
char *convert_num(long int num, int base, int flags)
{
	static const char *digitsLower = "0123456789abcdef";
	static const char *digitsUpper = "0123456789ABCDEF";
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n =
	(flags & CONVERT_UNSIGNED) ? (unsigned long)num : (num < 0 ? -num : num);
	const char *array = (flags & CONVERT_LOWERCASE) ? digitsLower : digitsUpper;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	sign = '-';

	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * rm_comments - function replaces first instance of '#' with '\0'
 * @buf: address of the string to modify
 *
 * Return: Always 0;
 */
void rm_comments(char *buf)
{
	int i = 0;
	int comment_start = -1;

	while (buf[i] != '\0')
	{
		if (buf[i] == '#' && (i == 0 || buf[i - 1] == ' '))
		{
			comment_start = i;
			break;
			}
			i++;
		}
	if (comment_start != -1)
	buf[comment_start] = '\0';
}
