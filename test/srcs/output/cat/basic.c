#include "libfts.h"
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(void)
{
	int fd;

	printf("file: %s\n", __FILE__);
	if ((fd = open(__FILE__, O_RDONLY)) < 0)
	{
		printf("open failed\n");
		return (EXIT_FAILURE);
	}
	ft_cat(fd);
	return (EXIT_SUCCESS);
}
