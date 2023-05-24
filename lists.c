#include "shell.h"

/**
 * add_node - adds a nd to the start of the lst
 * @head: addrs of ptr to head nd
 * @str: the str field of node
 * @num: nd indx used by hstry
 *
 * Return: sz of list
 */
list_t *add_node(list_t **head, const char *str, int num)
{
	list_t *n_hd;

	if (!head)
		return (NULL);
	n_hd = malloc(sizeof(list_t));
	if (!n_hd)
		return (NULL);
	_memset((void *)n_hd, 0, sizeof(list_t));
	n_hd->num = num;
	if (str)
	{
		n_hd->str = _strdup(str);
		if (!n_hd->str)
		{
			free(n_hd);
			return (NULL);
		}
	}
	n_hd->next = *head;
	*head = n_hd;
	return (n_hd);
}

/**
 * add_node_end - it adds a nd to end of the list
 * @head: adrs of ptr to head nd
 * @str: the strg field of nd
 * @num: nd indx used by hstry
 *
 * Return: sz of list
 */
list_t *add_node_end(list_t **head, const char *str, int num)
{
	list_t *nw_nd, *nd;

	if (!head)
		return (NULL);

	nd = *head;
	nw_nd = malloc(sizeof(list_t));
	if (!nw_nd)
		return (NULL);
	_memset((void *)nw_nd, 0, sizeof(list_t));
	nw_nd->num = num;
	if (str)
	{
		nw_nd->str = _strdup(str);
		if (!nw_nd->str)
		{
			free(nw_nd);
			return (NULL);
		}
	}
	if (nd)
	{
		while (nd->next)
			nd = nd->next;
		nd->next = nw_nd;
	}
	else
		*head = nw_nd;
	return (nw_nd);
}

/**
 * print_list_str - it prnts only str elmt of list_t linked lst
 * @h: ptr to frst node
 *
 * Return: sz of lst
 */
size_t print_list_str(const list_t *h)
{
	size_t l = 0;

	while (h)
	{
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		l++;
	}
	return (l);
}

/**
 * delete_node_at_index - it deletes node at given idx
 * @head: the address of ptr to frst node
 * @index: idx of nd to delete
 *
 * Return: 1 on success, 0 on failure
 */
int delete_node_at_index(list_t **head, unsigned int index)
{
	list_t *nd, *pv_nd;
	unsigned int i = 0;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		nd = *head;
		*head = (*head)->next;
		free(nd->str);
		free(nd);
		return (1);
	}
	nd = *head;
	while (nd)
	{
		if (i == index)
		{
			pv_nd->next = nd->next;
			free(nd->str);
			free(nd);
			return (1);
		}
		i++;
		pv_nd = nd;
		nd = nd->next;
	}
	return (0);
}

/**
 * free_list - it frees all nds of list
 * @head_ptr: adrs of ptr to head nd
 *
 * Return: returns void
 */
void free_list(list_t **head_ptr)
{
	list_t *nd, *nt_nd, *hd;

	if (!head_ptr || !*head_ptr)
		return;
	hd = *head_ptr;
	nd = hd;
	while (nd)
	{
		nt_nd = nd->next;
		free(nd->str);
		free(nd);
		nd = nt_nd;
	}
	*head_ptr = NULL;
}
