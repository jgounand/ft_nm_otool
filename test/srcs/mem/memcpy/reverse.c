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
			printf("memcpy failed at %zx, got %hhx wanted %hhx\n", i, p[i], t[i]);
			return (EXIT_FAILURE);
		}
	}

	memcpy(p, p + 5, SIZE - 5);
	ft_memcpy(t, t + 5, SIZE - 5);

	for (size_t i = 0; i < SIZE; i++)
	{
		if (p[i] != t[i])
		{
			printf("memcpy failed at %zx, got %hhx wanted %hhx\n", i, p[i], t[i]);
			return (EXIT_FAILURE);
		}
	}

	return (EXIT_SUCCESS);
}
