#include "libfts.h"
#include <string.h>
#include <stdio.h>

int	main(void)
{
	void *p1, *p2;

	p1 = ft_memset(NULL, 0, 0);
	p2 = memset(NULL, 0, 0);

	if (p1 != p2)
	{
		printf("memset failed got %p wanted %p\n", p1, p2);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
