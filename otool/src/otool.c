#include "../inc/ft_otool.h"
int	otool(char *ptr,size_t size,char *av)
{
	t_inf_header	inf_header;

	if ((inf_header = get_type_cpu(ptr,size)).error == 1)
		return (EXIT_FAILURE);
	inf_header.file = ptr;
	inf_header.size = size;
	inf_header.filename = av;
	if (inf_header.type == 1)
		return(handle_32_ot(inf_header));
	else if (inf_header.type == 2)
		return (handle_64_ot(inf_header));
	else if (inf_header.type == 3)
		return(handle_fat_ot(inf_header));
	else if (inf_header.type == 4)
		return(handle_ar_ot(inf_header));
	return (EXIT_FAILURE);
}

int	open_mmmap_work_close(char *path)
{
	int	fd;
	char	*file;
	struct	stat buf;

	if ((fd = open(path, O_RDONLY)) < 0 || fstat(fd,&buf) < 0)
	{
		ft_putstr_fd("ERROR open !\n",2);
		return (EXIT_FAILURE);
	}
	if ((file = mmap(0, buf.st_size, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
	{
		ft_putstr_fd("ERROR mmap !",2);
		return (EXIT_FAILURE);
	}
	int i = otool(file,buf.st_size,path);
	if (munmap(file, buf.st_size) < 0)
	{
		ft_putstr_fd("ERROR munmap !",2);
		return (EXIT_FAILURE);
	}
	return (i);
}
int	parse_av(int ac, char **av)
{
	bool exit;
	int	i;

	if (ac == 1)
		return (open_mmmap_work_close("a.out"));
	i = 1;
	while (i < ac)
	{
		ft_putstr(av[i]);
		ft_putstr(":\n");
		if (!exit)
			exit = open_mmmap_work_close(av[i]);
		else
			open_mmmap_work_close(av[i]);
		i++;
		ft_putchar('\n');
	}
	return (exit);
}

int	main(int ac, char **av)
{
	return (parse_av(ac,av));
}
