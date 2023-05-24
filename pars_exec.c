#include "shell.h"

/**
 * exec_cmd - determines if a file is an executable command
 * @strct: the info struct
 * @path: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int exec_cmd(struc_t *strct, char *path)
{
	struct stat st;

	(void)strct;
	if (!path || stat(path, &st))
		return (0);
	return ((st.st_mode & S_IFREG) ? 1 : 0);

}

/**
 * duplicat_char - duplicates characters
 * @pathstr: the PATH string
 * @start: starting index
 * @stop: stopping index
 *
 * Return: pointer to new buffer
 */
char *duplicat_char(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int i = 0, k = 0;

	for (k = 0, i = start; i < stop; i++)
		if (pathstr[i] != ':')
			buf[k++] = pathstr[i];
	buf[k] = 0;
	return (buf);
}

/**
 * search_path - finds this cmd in the PATH string
 * @strct: the info struct
 * @pathstr: the PATH string
 * @cmd: the cmd to find
 *
 * Return: full path of cmd if found or NULL
 */

char *search_path(struc_t *strct, char *pathstr, char *cmd)
	{
	int i = 0, curr_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((lenGTH_str(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (exec_cmd(strct, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[i] || pathstr[i] == ':')
		{
			path = duplicat_char(pathstr, curr_pos, i);
			if (!*path)
				concat_2str(path, cmd);
			else
			{
				concat_2str(path, "/");
				concat_2str(path, cmd);
			}
			if (exec_cmd(strct, path))
				return (path);
			if (!pathstr[i])
				break;
			curr_pos = i;
		}
		i++;
	}
	return (NULL);
}
