#include "shell.h"

/**
 * get_fstory - gets the history file
 * @strct: parameter struct
 *
 * Return: allocated string containg history file
 */

char *get_fstory(struc_t *strct)
{
	char *buf, *dir;

	dir = get_env(strct, "HOME=");
	if (!dir)
		return (NULL);
	size_t buf_len = lenGTH_str(dir) + lenGTH_str(HIST_FILE) + 2;

	buf = malloc(sizeof(char) * buf_len);
	if (!buf)
		return (NULL);
	_strcpy(buf, dir);
	concat_2str(buf, "/");
	concat_2str(buf, HIST_FILE);
	return (buf);
}

/**
 * wr_story - creates a file, or appends to an existing file
 * @strct: the parameter struct
 *
 * Return: 1 on success, else -1
 */
int wr_story(struc_t *strct)
{
	char *filename = get_fstory(strct);

	if (!filename)
		return (-1);

	ssize_t fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);

	free(filename);

	if (fd == -1)
		return (-1);

	for (lis_t *node = strct->history; node; node = node->next)
	{
		puts_filedescript(node->str, fd);
		put_fdescript('\n', fd);
	}
	put_fdescript(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * build_liststory - adds entry to a history linked list
 * @strct: Structure containing potential arguments. Used to maintain
 * @buf: buffer
 * @linecount: the history linecount, histcount
 *
 * Return: Always 0
 */
int build_liststory(struc_t *strct, char *buf, int linecount)
{
	lis_t *node = NULL;

	if (strct->history)
		node = strct->history;
	add_node_e(&node, buf, linecount);

	if (!strct->history)
		strct->history = node;
	return (0);
}

/**
 * reset_story - renumbers the history linked list after changes
 * @strct: Structure containing potential arguments. Used to maintain
 *
 * Return: the new histcount
 */
int reset_story(struc_t *strct)
{
	lis_t *node = strct->history;
	int i = 0;

	while (node != NULL)
	{
		node->num = i++;
		node = node->next;
	}
	strct->histcount = i;
	return (i);
}

/**
 * rd_story - reads history from file
 * @strct: the parameter struct
 *
 * Return: histcount on success, 0 otherwise
 */
int rd_story(struc_t *strct)
{
	int i, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = get_fstory(strct);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			build_liststory(strct, buf + last, linecount++);
			last = i + 1;
		}
	if (last != i)
		build_liststory(strct, buf + last, linecount++);
	free(buf);
	strct->histcount = linecount;
	while (strct->histcount-- >= HIST_MAX)
		deletenode_index(&(strct->history), 0);
	reset_story(strct);
	return (strct->histcount);
}


