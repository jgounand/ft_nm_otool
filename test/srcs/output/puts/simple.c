#include "libfts.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

# define BUFF_SIZE 1000
static int test_puts(char *s)
{
	int t1, t2;
	int pip[2];
	int dup_stdout;
	int r;
	char b1[BUFF_SIZE], b2[BUFF_SIZE];

	pipe(pip);
	dup_stdout = dup(STDOUT_FILENO);
	dup2(pip[1], STDOUT_FILENO);

	t1 = ft_puts(s);
	r = read(pip[0], b1, BUFF_SIZE);
	b1[r] = 0;

	t2 = puts(s);
	fflush(stdout);
	r = read(pip[0], b2, BUFF_SIZE);
	b2[r] = 0;

	close(pip[0]);
	close(pip[1]);
	dup2(dup_stdout, STDOUT_FILENO);
	close(dup_stdout);

	if (t1 != t2)
	{
		printf("failed puts got %d wanted %d\n", t1, t2);
		return (EXIT_FAILURE);
	}
	if ((r = strcmp(b1, b2)))
	{
		printf("failed puts, strcmp(%d)\nft_ > %s\noff > %s\n", r, b1, b2);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

#define S1 "bonjour je suis un string"
#define S2 ""
#define S3 "sdfaskjdflkashdf;lgjsdlkfjgljdlvjkblcjvkb;j;vkbj;lfkj;gljh;dfkjg;h" \
	"dfasdfsdfaskjdflkashdf;lgjsdlkfjgljdlvjkblcjvkb;j;vkbj;lfkj;gljh;dfkjg;h" \
	"dfasdfsdfaskjdflkashdf;lgjsdlkfjgljdlvjkblcjvkb;j;vkbj;lfkj;gljh;dfkjg;h" \
	"dfasdfsdfaskjdflkashdf;lgjsdlkfjgljdlvjkblcjvkb;j;vkbj;lfkj;gljh;dfkjg;h" \
	"dfasdfsdfaskjdflkashdf;lgjsdlkfjgljdlvjkblcjvkb;j;vkbj;lfkj;gljh;dfkjg;h" \
	"dfasdfsdfaskjdflkashdf;lgjsdlkfjgljdlvjkblcjvkb;j;vkbj;lfkj;gljh;dfkjg;h" \
	"dfasdfsdfaskjdflkashdf;lgjsdlkfjgljdlvjkblcjvkb;j;vkbj;lfkj;gljh;dfkjg;h" \
	"dfasdfsdfaskjdflkashdf;lgjsdlkfjgljdlvjkblcjvkb;j;vkbj;lfkj;gljh;dfkjg;h" \
	"dfasdfsdfaskjdflkashdf;lgjsdlkfjgljdlvjkblcjvkb;j;vkbj;lfkj;gljh;dfkjg;h" \
	"dfasdfsdfaskjdflkashdf;lgjsdlkfjgljdlvjkblcjvkb;j;vkbj;lfkj;gljh;dfkjg;h"
#define S4 "\x4"
#define S5 "\n\n\n\n"
#define S6 "\n\x4"

# define SIZE_STRINGS sizeof(strings) / sizeof(strings[0])

int	main(void)
{
	char	*strings[] = {
		S1, S2, S3, S4, S5, S6
	};

	for (size_t i = 0; i < SIZE_STRINGS; i++)
	{
		dprintf(2, "test string n°%zu\n", i);
		if (test_puts(strings[i]))
			return (EXIT_FAILURE);
	}

	return (EXIT_SUCCESS);
}
