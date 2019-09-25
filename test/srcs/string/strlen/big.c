#include "libfts.h"
#include <string.h>
#include <stdio.h>

# define SIZE (0x800ULL * 0x800ULL)
int	main(void)
{
	char	*s;
	size_t	s1;
	size_t	s2;

	s = malloc(SIZE + 1);
	if (s == NULL)
		return (EXIT_FAILURE);
	memset(s, 42, SIZE);
	s[SIZE] = 0;
	s1 = ft_strlen(s);
	s2 = strlen(s);
	if (s1 != s2)
	{
		printf("strlen failed for big string of size %llu, ft_(%zu), off(%zu)\n", SIZE, s1, s2);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
