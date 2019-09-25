#include "libfts.h"
#include <stdio.h>
#include <string.h>

int	main(void)
{
	const char	s[] = "bonjour je suis la";
	size_t		s1;
	size_t		s2;

	s1 = ft_strlen(s);
	s2 = strlen(s);
	if (s1 != s2)
	{
		printf("basic strlen failed got %zu wanted %zu\n", s1, s2);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
