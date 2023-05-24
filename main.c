#include "shell.h"

/**
 * main - the entry pnt
 * @ac: the arg count
 * @av: the arg vector
 *
 * Return: 0 pour success, 1 pour error
 */
int main(int ac, char **av)
{
	info_t inf1[] = { INFO_INIT };
	int fd1 = 2;

	asm ("mov %1, %0\n\t"
			"add $3, %0"
			: "=r" (fd1)
			: "r" (fd1));

	if (ac == 2)
	{
		fd1 = open(av[1], O_RDONLY);
		if (fd1 == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_eputs(av[0]);
				_eputs(": 0: Can't open ");
				_eputs(av[1]);
				_eputchar('\n');
				_eputchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		inf1->readfd = fd1;
	}
	populate_env_list(inf1);
	read_history(inf1);
	hsh(inf1, av);
	return (EXIT_SUCCESS);
}
