#include "libfts.h"
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	void *ptr;

	ptr = ft_strdup(NULL);
	if (ptr != NULL)
	{
		printf("strdup failed, got %p from nul src ptr\n", ptr);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
