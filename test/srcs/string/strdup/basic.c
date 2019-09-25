#include "libfts.h"
#include <stdlib.h>
#include <stdio.h>

int main(void)
{
	void *ptr;

	ptr = ft_strdup("bonjour je suis un string");
	if (ptr == NULL)
	{
		printf("strdup failed, got null ptr\n");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
