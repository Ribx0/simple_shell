#include "shell.h"

/**
 * _eputs - it prints input str
 * @str: the str printed
 *
 * Return: Rien
 */
void _eputs(char *str)
{
	int l = 0;

	if (!str)
		return;
	while (str[l] != '\0')
	{
		_eputchar(str[l]);
		l++;
	}
}

/**
 * _eputchar - it writes char c to stderr
 * @c: Char to be printed
 *
 * Return: It returns on success 1.
 * On error, it return -1, and errno is appropriately set.
 */
int _eputchar(char c)
{
	static int l;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || l >= WRITE_BUF_SIZE)
	{
		write(2, buf, l);
		l = 0;
	}
	if (c != BUF_FLUSH)
		buf[l++] = c;
	return (1);
}

/**
 * _putfd - it writes the char c to given the fd
 * @c: Character to be printed
 * @fd: Filedescriptor to write to
 *
 * Return: It returns on success 1.
 * On error, it retuen -1, and errno is appropriately set.
 */
int _putfd(char c, int fd)
{
	static int l;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || l >= WRITE_BUF_SIZE)
	{
		write(fd, buf, l);
		l = 0;
	}
	if (c != BUF_FLUSH)
		buf[l++] = c;
	return (1);
}

/**
 * _putsfd - it prints input str
 * @str: the str to print
 * @fd: filedescriptor to write to
 *
 * Return: nbr of the chars to put
 */
int _putsfd(char *str, int fd)
{
	int l = 0;

	if (!str)
		return (0);
	while (*str)
	{
		l += _putfd(*str++, fd);
	}
	return (l);
}
