#include "shell.h"

/**
 * input_buf - buffers chained commands
 * @strct: parameter struct
 * @buf: address of buffer
 * @len: address of len var
 *
 * Return: bytes read
 */
ssize_t input_buf(struc_t *strct, char **buf, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*len)
	{

		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);

		#if USE_GETLINE
		r = getline(buf, &len_p, stdin);
		#else
		r = _getline(strct, buf, &len_p);
		#endif

		if (r > 0)
		{
			if ((*buf)[r - 1] == '\n')
			{
				(*buf)[r - 1] = '\0';
				r--;
			}

			strct->linecount_flag = 1;
			rm_comments(*buf);
			build_liststory(strct, *buf, strct->histcount++);
			*len = r;
			strct->cmd_buf = buf;

		}
	}
	return (r);
}

/**
 * get_input - gets a line minus the newline
 * @strct: parameter struct
 *
 * Return: bytes read
 */
ssize_t get_input(struc_t *strct)
{
	static char *buf;
	static size_t i, j, len;
	ssize_t r = 0;
	char **buf_p = &(strct->arg), *p;

	_putchar(BUF_FLUSH);
	r = input_buf(strct, &buf, &len);
	if (r == -1)
		return (-1);
	if (len)
	{
		j = i;
		p = buf + i;

		check_chain(strct, buf, &j, i, len);

		for (; j < len; j++)
		{
			if (is_chain(strct, buf, &j))
			break;
		}

		i = j + 1;

		if (i >= len)
		{
			i = len = 0;
			strct->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p;
		return (lenGTH_str(p));
	}

	*buf_p = buf;
	return (r);
}

/**
 * read_buf - reads a buffer
 * @strct: parameter struct
 * @buf: buffer
 * @i: size
 *
 * Return: r
 */
ssize_t read_buf(struc_t *strct, char *buf, size_t *i)
{
	ssize_t r = 0;

	if (!*i)
		return (0);

	r = read(strct->readfd, buf, READ_BUF_SIZE);
	if (r >= 0)
		*i = r;
	return (r);
}

/**
 * _getline - gets the next line of input from STDIN
 * @strct: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: s
 */
int _getline(struc_t *strct, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (i == len)
		i = len = 0;

	r = read_buf(strct, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = chr_str(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = realloc_memory(p, s, s ? s + k : k + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (s)
		ncat_str(new_p, buf + i, k - i);
	else
		ncpy_str(new_p, buf + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * sigintHandler - blocks ctrl-C
 * @sig_num: the signal number
 *
 * Return: void
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
