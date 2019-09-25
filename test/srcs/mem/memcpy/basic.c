#include "libfts.h"
#include <string.h>
#include <stdio.h>

#define SIZE 42
#define VAL 0x12

int main(void)
{
	char src[SIZE];
	char dst[SIZE];
	void *p;

	printf("dst(%p), src(%p)\n", dst, src);
	memset(src, VAL, SIZE);
	p = ft_memcpy(dst, src, SIZE);
	if (p != dst)
	{
		printf("memcpy failed, got %p wanted %p\n", p, dst);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
