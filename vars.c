#include "shell.h"

/**
 * is_chain - test si current char in buffr is a chain delimeter
 * @info: the parmtr struct
 * @buf: char bufr
 * @p: address of current position in bufr
 *
 * Return: 1 si chain delimeter, 0 sinon
 */
int is_chain(info_t *info, char *buf, size_t *p)
{
	size_t l = *p;

	if (buf[l] == '|' && buf[l + 1] == '|')
	{
		buf[l] = 0;
		l++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[l] == '&' && buf[l + 1] == '&')
	{
		buf[l] = 0;
		l++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[l] == ';') /* found end of this command */
	{
		buf[l] = 0; /* replace semicolon with null */
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = l;
	return (1);
}

/**
 * check_chain - it checks should chaining based on the last status
 * @info: parmtr struct
 * @buf: charc bufr
 * @p: the adrs of current post in buffr
 * @i: start position in buffr
 * @len: the len of buffr
 *
 * Return: The void
 */
void check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t l = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			l = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			l = len;
		}
	}

	*p = l;
}

/**
 * replace_alias - it replaces an aliases in the tokenized str
 * @info: partr struct
 *
 * Return: return 1 if replaced, 0 otherwise
 */
int replace_alias(info_t *info)
{
	int l;
	list_t *nd;
	char *pr;

	for (l = 0; l < 10; l++)
	{
		nd = node_starts_with(info->alias, info->argv[0], '=');
		if (!nd)
			return (0);
		free(info->argv[0]);
		pr = _strchr(nd->str, '=');
		if (!pr)
			return (0);
		pr = _strdup(pr + 1);
		if (!pr)
			return (0);
		info->argv[0] = pr;
	}
	return (1);
}

/**
 * replace_vars - replaces vars in the tokenized str
 * @info: the parmtr struct
 *
 * Return: returns 1 if replaced, 0 otherwise
 */
int replace_vars(info_t *info)
{
	int l = 0;
	list_t *nd;

	for (l = 0; info->argv[l]; l++)
	{
		if (info->argv[l][0] != '$' || !info->argv[l][1])
			continue;

		if (!_strcmp(info->argv[l], "$?"))
		{
			replace_string(&(info->argv[l]),
					_strdup(convert_number(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[l], "$$"))
		{
			replace_string(&(info->argv[l]),
					_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		nd = node_starts_with(info->env, &info->argv[l][1], '=');
		if (nd)
		{
			replace_string(&(info->argv[l]),
					_strdup(_strchr(nd->str, '=') + 1));
			continue;
		}
		replace_string(&info->argv[l], _strdup(""));
	}
	return (0);
}

/**
 * replace_string - it replaces str
 * @old: the addrs of old str
 * @new: new str
 *
 * Return: 1 if replaced, else 0
 */
int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
