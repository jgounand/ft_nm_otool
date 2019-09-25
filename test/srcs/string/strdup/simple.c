#include "libfts.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

# define SIZE_STRING sizeof(strings) / sizeof(strings[0])

# define S1 "Bonjour je suis la"
# define S2 "Bonjour je suis la, un\x04e avec\tdes c\vhar bizarre\n"
# define S3 "une chaine plus longue, beaucoup plus longue, beaucoup plus long" \
	"ue, beaucoup plus longue, beaucoup plus longue, beaucoup plus longue, b" \
	"eaucoup plus longue, beaucoup plus longue, beaucoup plus longue, une ch" \
	"aine plus longue, beaucoup plus longue, beaucoup plus longue, beaucoup " \
	"plus longue, beaucoup plus longue, beaucoup plus longue, beaucoup plus " \
	"longue, beaucoup plus longue, beaucoup plus longue, une chaine plus lon" \
	"gue, beaucoup plus longue, beaucoup plus longue, beaucoup plus longue, " \
	"beaucoup plus longue, beaucoup plus longue, beaucoup plus longue, beauc" \
	"oup plus longue, beaucoup plus longue, une chaine plus longue, beaucoup" \
	" plus longue, beaucoup plus longue, beaucoup plus longue, beaucoup plus" \
	" longue, beaucoup plus longue, beaucoup plus longue, beaucoup plus long" \
	"ue, beaucoup plus longue"

int main(void)
{
	char	*strings[] = {
		S1, S2, S3
	};
	char	*t;

	for (size_t i = 0; i < SIZE_STRING; i++)
	{
		printf("test string n°%zu %p\n", i, strings[i]);
		t = ft_strdup(strings[i]);
		if (t == NULL)
		{
			printf("strdup failed, got null ptr\n");
			return (EXIT_FAILURE);
		}
		if (strcmp(t, strings[i]))
		{
			printf("strdup failed, string differ\nft_ > %s\noff > %s\n", t, strings[i]);
			return (EXIT_FAILURE);
		}
		free(t);
	}

	return (EXIT_SUCCESS);
}
