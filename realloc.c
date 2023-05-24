#include "shell.h"

/**
 * _memset - it fills mmry with a const byte
 * @s: ptr to the mmry area
 * @b: byte to fill *s with
 * @n: amount of bytes to filled
 * Return: (s) a pntr to the mmry area s
 */
char *_memset(char *s, char b, unsigned int n)
{
	unsigned int l;

	for (l = 0; l < n; l++)
		s[l] = b;
	return (s);
}

/**
 * ffree - it frees str of strs
 * @pp: the str of strs
 */
void ffree(char **pp)
{
	char **n = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(n);
}

/**
 * _realloc - it reallocates a block of mmry
 * @ptr: ptr to prvs malloc'ated block
 * @old_size: the byte sz of prvs block
 * @new_size: the byte sz of nw block
 *
 * Return: returns ptr to da ol'block nameen.
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *p1;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	p1 = malloc(new_size);
	if (!p1)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		p[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (p1);
}
