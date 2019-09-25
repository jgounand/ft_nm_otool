#include "libfts.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(int ac, char **av)
{
	int fd;

	if (ac < 2)
		return (EXIT_SUCCESS);
	if ((fd = open(av[1], O_RDONLY)) < 0)
	{
		dprintf(STDERR_FILENO, "failed open file %s\n", av[1]);
		return (EXIT_FAILURE);
	}
	ft_cat(fd);
	close(fd);
	return (EXIT_SUCCESS);
}
