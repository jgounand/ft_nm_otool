/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otool.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgounand <joris@gounand.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 11:18:36 by jgounand          #+#    #+#             */
/*   Updated: 2019/09/17 19:00:06 by jgounand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_otool.h"

static int	open_mmmap_work_close(char *path)
{
	int			fd;
	char		*file;
	struct stat	buf;
	int			i;

	if ((fd = open(path, O_RDONLY)) < 0 || fstat(fd, &buf) < 0)
	{
		ft_putstr_fd("ERROR open !\n", 2);
		return (EXIT_FAILURE);
	}
	if ((file = mmap(0, buf.st_size, PROT_READ | PROT_WRITE,
					MAP_PRIVATE, fd, 0)) == MAP_FAILED)
	{
		ft_putstr_fd("ERROR mmap !", 2);
		return (EXIT_FAILURE);
	}
	i = otool(file, buf.st_size, path);
	if (munmap(file, buf.st_size) < 0)
	{
		ft_putstr_fd("ERROR munmap !", 2);
		return (EXIT_FAILURE);
	}
	return (i);
}

static int	parse_av(int ac, char **av)
{
	bool	exit;
	int		i;

	if (ac == 1)
		return (open_mmmap_work_close("a.out"));
	i = 1;
	while (i < ac)
	{
		ft_putstr(av[i]);
		if (!exit)
			exit = open_mmmap_work_close(av[i]);
		else
			open_mmmap_work_close(av[i]);
		i++;
		ft_putchar('\n');
	}
	return (exit);
}

int			otool(char *ptr, size_t size, char *av)
{
	t_inf_header	inf_header;

	if ((inf_header = get_type_cpu(ptr, size)).error == 1)
		return (EXIT_FAILURE);
	inf_header.file = ptr;
	inf_header.size = size;
	inf_header.filename = av;
	if (inf_header.type == 1)
		return (handle_32_ot(inf_header));
	else if (inf_header.type == 2)
		return (handle_64_ot(inf_header));
	else if (inf_header.type == 3)
		return (handle_fat_ot(inf_header));
	else if (inf_header.type == 4)
		return (handle_ar_ot(inf_header));
	return (EXIT_FAILURE);
}

int			main(int ac, char **av)
{
	return (parse_av(ac, av));
}
