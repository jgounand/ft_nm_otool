#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include "libfts.h"

#define NB_ITEM 2048
#define SIZE_MEM (NB_ITEM * sizeof(uint8_t))

int		main(void)
{
	uint8_t	*mem;

	mem = (uint8_t*)malloc(SIZE_MEM); // malloc
	if (mem == NULL)
		return (EXIT_FAILURE);
	memset(mem, 42, SIZE_MEM);
	ft_bzero(mem, SIZE_MEM);
	return (EXIT_SUCCESS);
}
