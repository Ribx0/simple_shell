#include "shell.h"

/**
 * is_cmd - it dtrms if a file is executable comd
 * @info: info str
 * @path: the path to the file
 *
 * Return: 1 if true, else 0
 */
int is_cmd(info_t *info, char *path)
{
	struct stat st1;

	(void)info;
	if (!path || stat(path, &st1))
		return (0);

	if (st1.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_chars - it duplicates chars
 * @pathstr: the PATH str
 * @start: start the idx
 * @stop: stop the idx
 *
 * Return: ptr to new bfr
 */
char *dup_chars(char *pathstr, int start, int stop)
{
	static char buf1[1024];
	int l = 0, kh = 0;

	for (kh = 0, l = start; l < stop; l++)
		if (pathstr[l] != ':')
			buf1[kh++] = pathstr[l];
	buf1[kh] = 0;
	return (buf1);
}

/**
 * find_path - it finds this comd in the path str
 * @info: info of struct
 * @pathstr: the PATH strg
 * @cmd: comd to find
 *
 * Return: returns full path comd if found or NULL
 */
char *find_path(info_t *info, char *pathstr, char *cmd)
{
	int l = 0, c_p = 0;
	char *ph;

	if (!pathstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[l] || pathstr[l] == ':')
		{
			ph = dup_chars(pathstr, c_p, l);
			if (!*ph)
				_strcat(ph, cmd);
			else
			{
				_strcat(ph, "/");
				_strcat(ph, cmd);
			}
			if (is_cmd(info, ph))
				return (ph);
			if (!pathstr[l])
				break;
			c_p = l;
		}
		l++;
	}
	return (NULL);
}
