#include "libfts.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define BUFF_SIZE 1000

static int	exec_puts(char *s, char *buff, int (*f)(const char *))
{
	int		rt;
	int		r;
	int		pip[2];

	pipe(pip);
	dup2(pip[1], STDOUT_FILENO);
	rt = f(s);
	fflush(stdout);
	close(pip[1]);
	r = read(pip[0], buff, BUFF_SIZE);
	if (r == -1)
	{
		dprintf(STDERR_FILENO, "read error\n");
		return (EXIT_FAILURE);
	}
	buff[r] = 0;
	close(pip[0]);
	return (rt);
}

int	main(void)
{
	char	s1[] = "bonjour je suis un string\n";
	char	buff1[BUFF_SIZE], buff2[BUFF_SIZE];
	int		t1, t2;
	int		save_stdout;

	memset(buff1, 0, BUFF_SIZE);
	memset(buff2, 0, BUFF_SIZE);
	save_stdout = dup(STDOUT_FILENO);
	t1 = exec_puts(s1, buff1, ft_puts);
	dup2(save_stdout, STDOUT_FILENO);
	t2 = exec_puts(s1, buff2, puts);
	dup2(save_stdout, STDOUT_FILENO);
	close(save_stdout);
	if (t1 != t2)
	{
		printf("failed puts got %d wanted %d\n", t1, t2);
		return (EXIT_FAILURE);
	}
	if (strcmp(buff1, buff2))
	{
		printf("puts failed output differ\nft_ > %s\noff > %s\n", buff1, buff2);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
