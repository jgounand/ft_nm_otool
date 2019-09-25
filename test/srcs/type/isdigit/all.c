#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include "libfts.h"

# define MAX_VALUE 2048

int	main(void)
{
	int v1;
	int v2;

	for (size_t i = 0; i < MAX_VALUE; i++)
	{
		v1 = ft_isdigit(i);
		v2 = isdigit(i);
		if (v1 != v2)
		{
			printf("failed for value %zu, ft(%d) off(%d)\n", i, v1, v2);
			return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}
