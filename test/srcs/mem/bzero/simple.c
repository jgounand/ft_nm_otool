#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include "libfts.h"

#define NB_ITEM 2049
#define SIZE_MEM (NB_ITEM * sizeof(uint8_t))

int		main(void)
{
	uint8_t	*mem;

	if (!(mem = (uint8_t*)malloc(SIZE_MEM)))
		return (EXIT_FAILURE);
	memset(mem, 42, SIZE_MEM);
	ft_bzero(mem, SIZE_MEM);
	for (size_t i = 0; i < NB_ITEM; i++)
	{
		if (mem[i] != 0)
		{
			printf("bzero failed found value %x at %zx\n", mem[i], i);
			for (size_t j = 0; j < NB_ITEM; j++)
			{
				printf("%hhx ", mem[j]);
			}
			puts("\n");
			return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}
