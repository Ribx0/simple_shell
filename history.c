#include "shell.h"

/**
 * get_history_file - it gets hstry file
 * @info: parmtr struct
 *
 * Return: allocated the strg containg hstry file
 */

char *get_history_file(info_t *info)
{
	char *buff, *dir1;

	dir1 = _getenv(info, "HOME=");
	if (!dir1)
		return (NULL);
	buff = malloc(sizeof(char) * (_strlen(dir1) + _strlen(HIST_FILE) + 2));
	if (!buff)
		return (NULL);
	buff[0] = 0;
	_strcpy(buff, dir1);
	_strcat(buff, "/");
	_strcat(buff, HIST_FILE);
	return (buff);
}

/**
 * write_history - it creates file, or appends to exsting file
 * @info: prmter struct
 *
 * Return: 1 si success, sinon -1
 */
int write_history(info_t *info)
{
	ssize_t fd1;
	char *filenm = get_history_file(info);
	list_t *nd = NULL;

	if (!filenm)
		return (-1);

	fd1 = open(filenm, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filenm);
	if (fd1 == -1)
		return (-1);
	for (nd = info->history; nd; nd = nd->next)
	{
		_putsfd(nd->str, fd1);
		_putfd('\n', fd1);
	}
	_putfd(BUF_FLUSH, fd1);
	close(fd1);
	return (1);
}

/**
 * read_history - it reads hstry from file
 * @info: the parmtr struct
 *
 * Return: histcount on success, else 0
 */
int read_history(info_t *info)
{
	int l, last = 0, linecount = 0;
	ssize_t fd1, rdlen, fsz = 0;
	struct stat st1;
	char *buff = NULL, *filenm = get_history_file(info);

	if (!filenm)
		return (0);

	fd1 = open(filenm, O_RDONLY);
	free(filenm);
	if (fd1 == -1)
		return (0);
	if (!fstat(fd1, &st1))
		fsz = st1.st_size;
	if (fsz < 2)
		return (0);
	buff = malloc(sizeof(char) * (fsz + 1));
	if (!buff)
		return (0);
	rdlen = read(fd1, buff, fsz);
	buff[fsz] = 0;
	if (rdlen <= 0)
		return (free(buff), 0);
	close(fd1);
	for (l = 0; l < fsz; l++)
		if (buff[l] == '\n')
		{
			buff[l] = 0;
			build_history_list(info, buff + last, linecount++);
			last = l + 1;
		}
	if (last != l)
		build_history_list(info, buff + last, linecount++);
	free(buff);
	info->histcount = linecount;
	while (info->histcount-- >= HIST_MAX)
		delete_node_at_index(&(info->history), 0);
	renumber_history(info);
	return (info->histcount);
}

/**
 * build_history_list - it adds entry to history linkedList
 * @info: Struct the containing potential args. Used to maintain
 * @buf: the buff
 * @linecount: history linecount, the histcount
 *
 * Return: Toujours 0
 */
int build_history_list(info_t *info, char *buf, int linecount)
{
	list_t *nd1 = NULL;

	if (info->history)
		nd1 = info->history;
	add_node_end(&nd1, buf, linecount);

	if (!info->history)
		info->history = nd1;
	return (0);
}

/**
 * renumber_history - it renumbers history linkedList after changes
 * @info: Struct the containing potential args. Used to maintain
 *
 * Return: new histcount
 */
int renumber_history(info_t *info)
{
	list_t *nd1 = info->history;
	int i = 0;

	while (nd1)
	{
		nd1->num = i++;
		nd1 = nd1->next;
	}
	return (info->histcount = i);
}
