#include "shell.h"

/**
 * input_buf - the buffrs chained comds
 * @info: the parmtr to be structed
 * @buf: the add of buffer
 * @len: theadd of len variable
 *
 * Return: it returns the bytes read
 */
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t r1 = 0;
	size_t len_p = 0;

	if (!*len) /* fill it, if nothing left in the buffer */
	{
		/*bfree((void **)info->cmd_buf);*/
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		r1 = getline(buf, &len_p, stdin);
#else
		r1 = _getline(info, buf, &len_p);
#endif
		if (r1 > 0)
		{
			if ((*buf)[r1 - 1] == '\n')
			{
				(*buf)[r1 - 1] = '\0'; /* remove trailing newline */
				r1--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);
			/* if (_strchr(*buf, ';')) is it a cmd chain? */
			{
				*len = r1;
				info->cmd_buf = buf;
			}
		}
	}
	return (r1);
}

/**
 * get_input - it gets line minus newline
 * @info: the parmtr struct
 *
 * Return: the bytes read
 */
ssize_t get_input(info_t *info)
{
	static char *buff; /* the ';' cmd chain buffer */
	static size_t l, m, ln;
	ssize_t r1 = 0;
	char **buf_p = &(info->arg), *ptr;

	_putchar(BUF_FLUSH);
	r1 = input_buf(info, &buff, &ln);
	if (r1 == -1) /* EOF */
		return (-1);
	if (ln) /* we have cmds left in the chain buff */
	{
		m = l; /* init the new iter to curr buffer pos */
		ptr = buff + l; /* get ptr for return */

		check_chain(info, buff, &m, l, ln);
		while (m < ln) /* iter to semicolon or end */
		{
			if (is_chain(info, buff, &m))
				break;
			m++;
		}

		l = m + 1; /* incr past nulled ';'' */
		if (l >= ln) /* reached end of buff? */
		{
			l = ln = 0; /* reset pos and len */
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = ptr; /* pass back ptr to curr comd pos */
		return (_strlen(ptr)); /* return len of curr cmd */
	}

	*buf_p = buff; /* else not a chain, pass back buff from the _getline() */
	return (r1); /* return len of buff from the _getline() */
}


/**
 * read_buf - it reads buff
 * @info: the parmtr struct
 * @buf: the buffer
 * @i: the size
 *
 * Return: r
 */
ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
	ssize_t r1 = 0;

	if (*i)
		return (0);
	r1 = read(info->readfd, buf, READ_BUF_SIZE);
	if (r1 >= 0)
		*i = r1;
	return (r1);
}

/**
 * _getline - it gets the next line of input from the STDIN
 * @info: parmtr struct
 * @ptr: the addr of ptr to buff, preallocated or NULL
 * @length: the sz of preallocated pointr buff if not NULL
 *
 * Return: the s
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t l, ln;
	size_t k;
	ssize_t r1 = 0, s1 = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s1 = *length;
	if (l == ln)
		l = ln = 0;

	r1 = read_buf(info, buf, &ln);
	if (r1 == -1 || (r1 == 0 && ln == 0))
		return (-1);

	c = _strchr(buf + l, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : ln;
	new_p = _realloc(p, s1, s1 ? s1 + k : k + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (s1)
		_strncat(new_p, buf + l, k - l);
	else
		_strncpy(new_p, buf + l, k - l + 1);

	s1 += k - l;
	l = k;
	p = new_p;

	if (length)
		*length = s1;
	*ptr = p;
	return (s1);
}


/**
 * sigintHandler - it blocks ctrl-C
 * @sig_num: signal nbr
 *
 * Return: returns void
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
