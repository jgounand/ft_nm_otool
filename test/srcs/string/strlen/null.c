#include "libfts.h"
#include <stdio.h>

int	main(void)
{
	int i;

	i = ft_strlen(NULL);
	printf("res = %d\n", i);
	return (i != 0);
}
