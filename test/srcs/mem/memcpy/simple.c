#include "libfts.h"
#include <string.h>
#include <stdio.h>

#define SIZE 42
#define VAL 0xa2
#define HEXDUMP "0123456789abcdef"
void dump(void *d, size_t size)
{
	uint8_t *data = d;
	char	*hex = HEXDUMP;
	for (size_t i = 0; i < size; i++)
	{
		putchar(hex[data[i] >> 4]);
		putchar(hex[data[i] & 0xf]);
		putchar(' ');
	}
	putchar('\n');
}

int main(void)
{
	char src[SIZE];
	char dst[SIZE];
	void *p;

	bzero(dst, SIZE);
	memset(src, VAL, SIZE);
	p = ft_memcpy(dst, src, SIZE);
	if (p != dst)
	{
		printf("memcpy failed, got %p wanted %p\n", p, dst);
		return (EXIT_FAILURE);
	}
	for (size_t i = 0; i < SIZE; i++)
	{
		if (dst[i] != src[i])
		{
			printf("memcpy failed at %zx, got %hhx wanted %hhx\n", i, dst[i], src[i]);
			printf("\ngot:\n");
			dump(dst, SIZE);
			printf("\nwanted:\n");
			dump(src, SIZE);
			return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}
