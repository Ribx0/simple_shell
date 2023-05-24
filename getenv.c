#include "shell.h"

/**
 * get_environ - it returns str array cp of our envrn
 * @info: Struct containing the potential args. Used to maintain
 *          const fct prototype.
 * Return: Toujours 0
 */
char **get_environ(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = list_to_strings(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * _unsetenv - Remove an envrnmnt var
 * @info: Struct the containing potential args. Used to maintain
 *        cont fct prototype.
 *  Return: 1 on dlt, 0 otherwise
 * @var: the str env var propt
 */
int _unsetenv(info_t *info, char *var)
{
	list_t *node = info->env;
	size_t l = 0;
	char *pt;

	if (!node || !var)
		return (0);

	while (node)
	{
		pt = starts_with(node->str, var);
		if (pt && *pt == '=')
		{
			info->env_changed = delete_node_at_index(&(info->env), l);
			l = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		l++;
	}
	return (info->env_changed);
}

/**
 * _setenv - Initialize the new envrnmt var,
 *             or mod the existing one
 * @info: Struct the containing potential args. Used to maintain
 *        const fct prototype.
 * @var: the str env var prop
 * @value: the str envrn var val
 *  Return: Toujours 0
 */
int _setenv(info_t *info, char *var, char *value)
{
	char *buf = NULL;
	list_t *nd;
	char *pt;

	if (!var || !value)
		return (0);

	buf = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buf)
		return (1);
	_strcpy(buf, var);
	_strcat(buf, "=");
	_strcat(buf, value);
	nd = info->env;
	while (nd)
	{
		pt = starts_with(nd->str, var);
		if (pt && *pt == '=')
		{
			free(nd->str);
			nd->str = buf;
			info->env_changed = 1;
			return (0);
		}
		nd = nd->next;
	}
	add_node_end(&(info->env), buf, 0);
	free(buf);
	info->env_changed = 1;
	return (0);
}
