#include "shell.h"

/**
 * bfree - it frees a ptr and NULLs the adrs
 * @ptr: it address of the ptr to free
 *
 * Return: 1 if freed, else 0.
 */
int bfree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
