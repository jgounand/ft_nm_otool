#include "../inc/ft_nm.h"

void	print_output(int nsyms, int symoff, int stroff, char *ptr)
{
	int				i;
	char			*stringtable;
	struct nlist_64	*array;

	array = (void *)ptr + symoff;
	stringtable =(void *) ptr + stroff;
	for (i =0; i <nsyms; ++i)
	{
		if ((array[i].n_type & N_TYPE) ==  N_UNDF)
			printf("TYPE N_UNDF ");
		else if ((array[i].n_type & N_TYPE) ==  N_ABS)
			printf("TYPE N_ABS ");
		else if ((array[i].n_type & N_TYPE) ==  N_SECT)
			printf("TYPE N_SECT %d ", array[i].n_sect);
		else if ((array[i].n_type & N_TYPE) ==  N_PBUD)
			printf("TYPE N_PBUD ");
		else if ((array[i].n_type & N_TYPE) ==  N_INDR)
			printf("TYPE N_INDR ");
		else
			printf("error ");
		if ((array[i].n_type & N_EXT))
			printf(" global ");
		printf("%s\n", stringtable + array[i].n_un.n_strx);
	}
}


void	handle_64(char	*ptr)
{
	int						ncmds;
	int						i;
	struct mach_header_64	*header;
	struct load_command		*lc;
	struct symtab_command		*sym;

	i = 0;
	header = (struct mach_header_64 *)ptr;
	ncmds = header->ncmds;
	lc = (void *)ptr + sizeof(*header);
	for (i = 0; i <ncmds; ++i)
	{
		if (lc->cmd == LC_SYMTAB)
		{
			sym = (struct symtab_command *) lc;
			print_output(sym->nsyms, sym->symoff, sym->stroff,ptr);
			break;
		}
		lc = (void *) lc + lc->cmdsize;
	}
}
int is_magic_64(uint32_t magic) {
  return magic == MH_MAGIC_64 || magic == MH_CIGAM_64;
}
int is_magic_32(uint32_t magic) {
  return magic == MH_MAGIC || magic == MH_CIGAM;
}
int should_swap_bytes(uint32_t magic) {
  return magic == MH_CIGAM || magic == MH_CIGAM_64;
}

int	place_for_header(size_t size)
{
	if (size >= sizeof(struct mach_header_64))
		return (2);
	else if (size >= sizeof(struct mach_header))
		return (1);
	return (0);
}


short is_match_header(uint32_t	magic_number, size_t size)
{
	int	_64;
	int	_32;

	_64 = 0;
	_32 = 0;
	if (place_for_header(size) == 1)
		_32 = is_magic_32(magic_number);
	else
	{
		_32 = is_magic_32(magic_number);
		_64 = is_magic_64(magic_number);
	}
	if (!_32 && !_64)
		return (0);
	printf("type _32 %d _64 %d\n",_32,_64);
	if (_32 == 1)
		return (1);
	else
		return (2);
}

t_inf_header	get_header(char *ptr, size_t size)
{
	t_inf_header	inf_header;
	short			i;
	uint32_t	magic_number;

	magic_number = *(int *)ptr;
	ft_bzero(&inf_header, sizeof(t_inf_header));
	if ((i = place_for_header(size)) == 0)
	{
		ft_putstr_fd("Error not the size for header\n",2);
		inf_header.error = 1;
		return (inf_header);
	}
	if ((i = is_match_header(magic_number,size)) == 0)
	{
		
		ft_putstr_fd("Error magic number\n",2);
		inf_header.error = 1;
		return (inf_header);
	}
	printf("i %d\n",i);
	inf_header.type = i - 1;
	inf_header.swap = should_swap_bytes(magic_number);
	return (inf_header);
}


void	nm(char *ptr,size_t size)
{
t_inf_header	inf_header;

	if ((inf_header = get_header(ptr,size)).error == 1)
		return ;
	if (inf_header.type == 1)
	{
	//need to swap the header
	}
	if (inf_header.type == 0)
	{
printf("enter hanfler_32\n");
	//handle_32
	}
	else
	{

printf("enter hanfler_64\n");
		handle_64(ptr);
	}
}


int	main(int ac, char **av)
{
	int	fd;
	char	*ptr;
	struct	stat buf;

	if (ac !=2)
	{
		printf("Give me a argument !");
		return (EXIT_FAILURE);
	}
	if ((fd = open(av[1], O_RDONLY)) < 0)
	{
	return (EXIT_FAILURE);
	}
	if (fstat(fd,&buf) <0)
	{
	return (EXIT_FAILURE);
	}
	if ((ptr = mmap(0, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
	{
		printf("ERROR mmap !");
	return (EXIT_FAILURE);
	}
	nm(ptr,buf.st_size);
	if (munmap(ptr, buf.st_size) < 0)
	{
		printf("ERROR munmap !");
	return (EXIT_FAILURE);

	}
	return (EXIT_SUCCESS);
}
