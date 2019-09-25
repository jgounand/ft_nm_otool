#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include "libfts.h"

#define NB_ITEM (2048 * 2048)
#define SIZE_MEM (NB_ITEM * sizeof(uint8_t))

int		main(void)
{
	uint8_t	*mem;

	printf("mem size %zu\n", SIZE_MEM);
	mem = (uint8_t*)malloc(SIZE_MEM);
	if (mem == NULL)
		return (EXIT_FAILURE);
	memset(mem, 42, SIZE_MEM);
	ft_bzero(mem, SIZE_MEM);
	for (size_t i = 0; i < NB_ITEM; i++)
	{
		if (mem[i] != 0)
		{
			printf("bzero failed found value %x at %zx\n", mem[i], i);
			return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}
