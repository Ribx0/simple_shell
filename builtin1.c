#include "shell.h"

/**
 * _myhistory - the history list is displays, 1 comd by line, preceded
 *              with line nbrs, 0 is the start.
 * @info: The Struct containing the potential args. Used to maintain
 *        const fct prototype.
 *  Return: Toujours 0
 */
int _myhistory(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * unset_alias - sets the alias to str
 * @info: the parmtr struct
 * @str: str alias
 *
 * Return: toujours 0 on success, and 1 on error
 */
int unset_alias(info_t *info, char *str)
{
	char *ptr, ch;
	int ret;

	ptr = _strchr(str, '=');
	if (!ptr)
		return (1);
	ch = *ptr;
	*ptr = 0;
	ret = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*ptr = ch;
	return (ret);
}


/**
 * set_alias - the sets alias to a str
 * @info: the parmt struct
 * @str: str alias
 *
 * Return: Toujours 0 pour success, et 1 pour error
 */
int set_alias(info_t *info, char *str)
{
	char *ptr;

	ptr = _strchr(str, '=');
	if (!ptr)
		return (1);
	if (!*++ptr)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - it prints the alias str
 * @node: node of the alias
 *
 * Return: Toujours 0 pour success, et 1 pour error
 */
int print_alias(list_t *node)
{
	char *ptr = NULL, *x = NULL;

	if (node)
	{
		ptr = _strchr(node->str, '=');
		for (x = node->str; x <= ptr; x++)
		_putchar(*x);
		_putchar('\'');
		_puts(ptr + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias - the alias are mimics builtin (man alias)
 * @info: Struct of the containing potential args. It is used to maintain
 *          const fct prototype.
 *  Return: Toujours 0
 */
int _myalias(info_t *info)
{
	int e = 0;
	char *ptr = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}

	for (e = 1; info->argv[e]; e++)
	{
		ptr = _strchr(info->argv[e], '=');
		if (ptr)
			set_alias(info, info->argv[e]);
		else
			print_alias(node_starts_with(info->alias, info->argv[e], '='));
	}

	return (0);
}
