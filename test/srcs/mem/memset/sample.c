#include "libfts.h"
#include <string.h>
#include <stdio.h>

#define SIZE (0x800Ull * 0x800)
#define SET 10

int	main(void)
{
	char	*p;

	p = malloc(SIZE);
	printf("%p\n", p);
	ft_memset(p, SET, SIZE);
	return (EXIT_SUCCESS);
}
