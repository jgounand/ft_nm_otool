/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgounand <joris@gounand.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 14:39:46 by jgounand          #+#    #+#             */
/*   Updated: 2019/09/17 15:27:51 by jgounand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_nm.h"

static int	open_mmmap_work_close(char *path)
{
	int			fd;
	char		*file;
	struct stat	buf;
	int			ret;

	if ((fd = open(path, O_RDONLY)) < 0 || fstat(fd, &buf) < 0)
	{
		ft_putstr_fd("ERROR open !\n", 2);
		return (EXIT_FAILURE);
	}
	if ((file = mmap(0, buf.st_size, PROT_READ | PROT_WRITE,
					MAP_PRIVATE, fd, 0)) == MAP_FAILED)
	{
		ft_putstr_fd("ERROR munmap !\n", 2);
		return (EXIT_FAILURE);
	}
	ret = nm(file, buf.st_size, path);
	if (munmap(file, buf.st_size) < 0)
	{
		ft_putstr_fd("ERROR munmap !\n", 2);
		return (EXIT_FAILURE);
	}
	return (ret);
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
		exit = open_mmmap_work_close(av[i]);
		i++;
	}
	return (exit);
}

int			sort_lst_nm(void *content, void *content_next)
{
	t_symbol	*tmp;
	t_symbol	*tmp2;
	int			ret;

	tmp = content;
	tmp2 = content_next;
	ret = ft_strcmp(tmp->sym_name, tmp2->sym_name);
	if (ret == 0)
		return (tmp->n_value > tmp2->n_value);
	return (ret > 0 ? 1 : 0);
}

int			nm(char *ptr, size_t size, char *av)
{
	t_inf_header	inf_header;

	if ((inf_header = get_type_cpu(ptr, size)).error == 1)
		return (EXIT_FAILURE);
	inf_header.file = ptr;
	inf_header.size = size;
	inf_header.filename = av;
	inf_header.tab_section = NULL;
	inf_header.size_section = 0;
	if (inf_header.type == 1)
		return (handle_32(&inf_header));
	else if (inf_header.type == 2)
		return (handle_64(&inf_header));
	else if (inf_header.type == 3)
		return (handle_fat(&inf_header));
	else if (inf_header.type == 4)
		return (handle_ar(&inf_header));
	return (EXIT_FAILURE);
}

int			main(int ac, char **av)
{
	return (parse_av(ac, av));
}
