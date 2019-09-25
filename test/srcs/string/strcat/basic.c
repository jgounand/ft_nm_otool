#include "libfts.h"
#include <stdio.h>
#include <string.h>

# define S1	"Bonjour je suis la"
# define S2 ", mais pas pour longtemps"
# define S1S2 S1 S2
# define SIZE (sizeof(S1) + sizeof(S2))

int	main(void)
{
	char	s1[SIZE] = S1;
	char	s2[] = S2;
	char	*ptr;

	printf("s1 %p s2 %p\n", s1, s2);
	ptr = ft_strcat(s1, s2);
	if (ptr != s1)
	{
		printf("strcat ptr not equal ret(%p) ori(%p)\n", ptr, s1);
		return (EXIT_FAILURE);
	}
	if (strcmp(ptr, S1S2))
	{
		printf("strcat string differ\nft_ > %s\noff > %s\n", ptr, S1S2);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
