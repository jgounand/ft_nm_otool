#include "libfts.h"
#include <stdio.h>

int main(void)
{
	void *p;
	void *r;

	p = (void*)0x123456789ULL;
	r = ft_memcpy(NULL, p, 42);
	if (r != NULL)
	{
		printf("memcpy failed, should return null ptr on dest null ptr\n");
		return (EXIT_FAILURE);
	}
	r = ft_memcpy(p, NULL, 42);
	if (r != NULL)
	{
		printf("memcpy failed, should return null ptr on src null ptr\n");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
