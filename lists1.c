#include "shell.h"

/**
 * list_len - it dtrmns len of linked list
 * @h: ptr to frst node
 *
 * Return: the size of the list
 */
size_t list_len(const list_t *h)
{
	size_t l = 0;

	while (h)
	{
		h = h->next;
		l++;
	}
	return (l);
}

/**
 * list_to_strings - it returns an arr of strs of the list->str
 * @head: ptr to frt nd
 *
 * Return: arr of strgs
 */
char **list_to_strings(list_t *head)
{
	list_t *nd = head;
	size_t l = list_len(head), m;
	char **strs1;
	char *str1;

	if (!head || !l)
		return (NULL);
	strs1 = malloc(sizeof(char *) * (l + 1));
	if (!strs1)
		return (NULL);
	for (l = 0; nd; nd = nd->next, l++)
	{
		str1 = malloc(_strlen(nd->str) + 1);
		if (!str1)
		{
			for (m = 0; m < l; m++)
				free(strs1[m]);
			free(strs1);
			return (NULL);
		}

		str1 = _strcpy(str1, nd->str);
		strs1[l] = str1;
	}
	strs1[l] = NULL;
	return (strs1);
}

/**
 * print_list - it prints all elmts of a list_t linked list
 * @h: ptr to frst nd
 *
 * Return: sz of lst
 */
size_t print_list(const list_t *h)
{
	size_t l = 0;

	while (h)
	{
		_puts(convert_number(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		l++;
	}
	return (l);
}

/**
 * node_starts_with - it returns nd whose str starts with prfx
 * @node: ptr to list head
 * @prefix: the str to match
 * @c: next char after prefix to match
 *
 * Return: match nd or null
 */
list_t *node_starts_with(list_t *node, char *prefix, char c)
{
	char *pt1 = NULL;

	while (node)
	{
		pt1 = starts_with(node->str, prefix);
		if (pt1 && ((c == -1) || (*pt1 == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * get_node_index - gets idx of nd
 * @head: ptr to lst head
 * @node: ptr to the nd
 *
 * Return: idx of nd or -1
 */
ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t l = 0;

	while (head)
	{
		if (head == node)
			return (l);
		head = head->next;
		l++;
	}
	return (-1);
}
