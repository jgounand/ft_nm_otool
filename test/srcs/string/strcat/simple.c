#include "libfts.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct	s_test
{
	const char *dst;
	const char *src;
}				t_test;

int	test_strcat(const char *dst, const char *src)
{
	size_t	ldst, lsrc;
	char	*s1, *s2, *r_ft;
	int		re;

	re = EXIT_SUCCESS;
	ldst = strlen(dst);
	lsrc = strlen(src);

	s1 = malloc(ldst + lsrc + 1);
	s2 = malloc(ldst + lsrc + 1);

	strcpy(s1, dst);
	strcpy(s2, dst);

	strcat(s2, src);
	r_ft = ft_strcat(s1, src);

	if (r_ft != s1)
	{
		re = EXIT_FAILURE;
		printf("strcat failed, return : got %p wanted %p\n", r_ft, s1);
	}
	else if (strcmp(s1, s2))
	{
		re = EXIT_FAILURE;
		printf("strcat failed, on dst(%s) src(%s)\n", dst, src);
		printf("got \"%s\" wanted \"%s\"\n", s1, s2);
	}

	free(s1);
	free(s2);
	return (re);
}

int	main(void)
{
	t_test test[] = {
		{"", ""},
		{"a", ""},
		{"", "a"},
		{"abc", ""},
		{"", "abc"},
		{"abc", "abc"},
		{"a", "abc"},
		{"abc", "a"},
		{"Une longue ", "chaine de char"},
		{"Une longue chaine", "de char"},
		{"Une longue chaine de char", ""},
		{"", "Une longue chaine de char"},
	};

	for (size_t i = 0; i < sizeof(test) / sizeof(test[0]); i++)
	{
		if (test_strcat(test[i].dst, test[i].src))
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
