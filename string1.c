#include "shell.h"

/**
 * _strcpy - it copies a str
 * @dest: the dest
 * @src: source
 *
 * Return: ptr to dest
 */
char *_strcpy(char *dest, char *src)
{
	int l = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[l])
	{
		dest[l] = src[l];
		l++;
	}
	dest[l] = 0;
	return (dest);
}

/**
 * _strdup - it duplicts a str
 * @str: str to duplicate
 *
 * Return: return ptr to duplicated str
 */
char *_strdup(const char *str)
{
	int len1 = 0;
	char *ret11;

	if (str == NULL)
		return (NULL);
	while (*str++)
		len1++;
	ret11 = malloc(sizeof(char) * (len1 + 1));
	if (!ret11)
		return (NULL);
	for (len1++; len1--;)
		ret11[len1] = *--str;
	return (ret11);
}

/**
 * _puts - it prints input str
 * @str: strg to print
 *
 * Return: Rien
 */
void _puts(char *str)
{
	int l = 0;

	if (!str)
		return;
	while (str[l] != '\0')
	{
		_putchar(str[l]);
		l++;
	}
}

/**
 * _putchar - it writes the char c to stdout
 * @c: char to be printed
 *
 * Return: success 1.
 * On error, -1 is returned, and errno is set.
 */
int _putchar(char c)
{
	static int l;
	static char buffr[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || l >= WRITE_BUF_SIZE)
	{
		write(1, buffr, l);
		l = 0;
	}
	if (c != BUF_FLUSH)
		buffr[l++] = c;
	return (1);
}
