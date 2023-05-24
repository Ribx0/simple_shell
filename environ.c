#include "shell.h"

/**
 * _myenv - it prints current envrnmnt
 * @info: Struct are containing the potential args. Used to maintain
 *          const fct prototype.
 * Return: Toujours 0
 */
int _myenv(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * _getenv - it gets the val of the environ var
 * @info: Struct are containing the potential args. Used to maintain
 * @name: the envrnmnt variable name
 *
 * Return: Value
 */
char *_getenv(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *ptr1;

	while (node)
	{
		ptr1 = starts_with(node->str, name);
		if (ptr1 && *ptr1)
			return (ptr1);
		node = node->next;
	}
	return (NULL);
}

/**
 * _mysetenv - Initialize a new envrnmnt var,
 *             or modify an ext 1
 * @info: Struct are containing the potential args. Are used to maintain
 *        const funct prototype.
 *  Return: Toujours 0
 */
int _mysetenv(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Incorrect nbr of args\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * _myunsetenv - Remove an envrnmnt var
 * @info: Struct are containing the potential args. Used to maintain
 *        const func prototype.
 * Return: Toujours 0
 */
int _myunsetenv(info_t *info)
{
	int l;

	if (info->argc == 1)
	{
		_eputs("Too few args.\n");
		return (1);
	}
	for (l = 1; l <= info->argc; l++)
		_unsetenv(info, info->argv[l]);

	return (0);
}

/**
 * populate_env_list - it populates the envrnmt linked liste
 * @info: Struct are containing the potential args. Used to maintain
 *          const funct prototype.
 * Return: Toujours 0
 */
int populate_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t l;

	for (l = 0; environ[l]; l++)
		add_node_end(&node, environ[l], 0);
	info->env = node;
	return (0);
}
