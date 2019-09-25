#include "libfts.h"
#include <string.h>
#include <stdio.h>

#define SIZE 42ULL
#define SET 10

int	main(void)
{
	char	*p;
	char	*p2;
	char	*pr;

	p = malloc(SIZE);
	p2 = malloc(SIZE);
	if (p == NULL || p2 == NULL)
		return (EXIT_FAILURE);
	pr = ft_memset(p, SET, SIZE);
	memset(p2, SET, SIZE);
	if (pr != p)
	{
		printf("memset failed got %p wanted %p\n", pr, p);
		return (EXIT_FAILURE);
	}
	for (size_t i = 0; i < SIZE; i++)
	{
		if (pr[i] != p2[i])
		{
			printf("memset failed at %zx, got %hhx wanted %x\n", i, pr[i], p2[i]);
			return (EXIT_FAILURE);
		}
	}

	return (EXIT_SUCCESS);
}
