#include "libfts.h"
#include <string.h>
#include <stdio.h>

#define DATA "bonjour je suis la"
#define SIZE sizeof(DATA)
#define OFFSET 5

int main(void)
{
	char p[SIZE];
	char t[SIZE];

	memcpy(p, DATA, SIZE);
	ft_memcpy(t, DATA, SIZE);

	for (size_t i = 0; i < SIZE; i++)
	{
		if (p[i] != t[i])
		{
			printf("memcpy init failed at %zx, got %hhx wanted %hhx\n", i, p[i], t[i]);
			return (EXIT_FAILURE);
		}
	}

	printf("off > %s\nft_ > %s\n", p, t);
	memcpy(p + 5, p, 5);
	ft_memcpy(t + 5, t, 5);

	for (size_t i = 0; i < SIZE; i++)
	{
		if (p[i] != t[i])
		{
			printf("memcpy forward failed at %zx, got %hhx wanted %hhx\n", i, p[i], t[i]);
			printf("off > %s\nft_ > %s\n", p, t);
			return (EXIT_FAILURE);
		}
	}

	return (EXIT_SUCCESS);
}
