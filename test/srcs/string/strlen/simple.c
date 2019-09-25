#include "libfts.h"
#include <string.h>
#include <stdio.h>

# define SIZE_STRINGS sizeof(strings) / sizeof(strings[0])
int	main(void)
{
	const char *strings[] = {
		""
		"bonjour je suis une string",
		"bonjour je suis une autre string",
		"cette fois ci je \x33 met\n de \t char \x01 bizz\varre\f dans la chaine"
	};
	size_t s1;
	size_t s2;

	for (size_t i = 0; i < SIZE_STRINGS; i++)
	{
		s1 = ft_strlen(strings[i]);
		s2 = strlen(strings[i]);
		if (s1 != s2)
		{
			printf("strlen for string \"%s\", ft_(%zu) off(%zu)\n", strings[i], s1, s2);
			return (EXIT_FAILURE);
		}
	}

	return (EXIT_SUCCESS);
}
