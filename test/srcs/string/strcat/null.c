#include "libfts.h"
#include <string.h>
#include <stdio.h>

#define S1 "bonjour je suis la"
#define S2 ", il fait beau"
#define SS1 sizeof(S1)
#define SS2	sizeof(S2)
#define SIZE (SS1 + SS2)

static int test_cat(char *s1, char *s2)
{
	char *sp;

	sp = ft_strcat(s1, s2);
	if (sp != s1)
	{
		printf("strcat failed for s1(%s) s2(%s)\n", s1, s2);
		printf("got ft_(%p) but want %p\n", sp, s1);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int main(void)
{
	char s1[SIZE] = S1;
	char s2[] = S2;

	if (test_cat(s1, NULL) == EXIT_FAILURE
		|| test_cat(NULL, s2) == EXIT_FAILURE
		|| test_cat(NULL, NULL) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
