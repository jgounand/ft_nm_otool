#include "../inc/ft_nm.h"

int	sort_lst_nm(void	*content, void	*content_next)
{
	t_symbol *tmp;
	t_symbol *tmp2;
	int		ret;

	tmp = content;
	tmp2 = content_next;
	ret = ft_strcmp(tmp->sym_name, tmp2->sym_name);
		if (ret == 0)
		return (tmp->n_value > tmp2->n_value);
	return(ret > 0? 1 : 0);
}
void	print_output(int nsyms, int symoff, int stroff, char *ptr, size_t size)
{
	int				i;
	char			*stringtable;
	struct nlist_64	*array;
	t_list	*new_lst;
	t_symbol new;

	array = (void *)ptr + symoff;
	stringtable =(void *) ptr + stroff;
	if (addr_outof_range(ptr,size,array) || addr_outof_range(ptr,size,stringtable))
	return ;
	new_lst = NULL;
	for (i =0; i <nsyms; ++i)
	{
	if (addr_outof_range(ptr,size,(void *)&array[i] + sizeof(struct nlist_64)))
	return ;
		if(array[i].n_type & N_STAB) {
			continue;
		}
		new.n_value = array[i].n_value;
		new.sym_type = ft_get_type_64(array[i],ptr,size);
		new.sym_name = stringtable + array[i].n_un.n_strx;
		new.n_value = array[i].n_value;
		new.cpu_type = 64;
		ft_lstadd(&new_lst,ft_lstnew(&new,sizeof(t_symbol)));
	}
;
	ft_lstsort(&new_lst, sort_lst_nm);
	ft_lstiter(new_lst,show_list);
}
void	print_output_32(int nsyms, int symoff, int stroff, char *ptr, size_t size)
{
	int				i;
	char			*stringtable;
	struct nlist	*array;
	t_list	*new_lst;
	t_symbol new;

	array = (void *)ptr + symoff;
	stringtable =(void *) ptr + stroff;
	if (addr_outof_range(ptr,size,array) || addr_outof_range(ptr,size,stringtable))
	return ;
	new_lst = NULL;
	for (i =0; i <nsyms; ++i)
	{
	if (addr_outof_range(ptr,size,(void *)&array[i] + sizeof(struct nlist_64)))
	return ;
		if(array[i].n_type & N_STAB) {
			continue;
		}
		new.n_value = array[i].n_value;
		new.sym_type = ft_get_type(array[i], ptr, size);
		new.sym_name = stringtable + array[i].n_un.n_strx;
		new.n_value = array[i].n_value;
		new.cpu_type = 32;
		ft_lstadd(&new_lst,ft_lstnew(&new,sizeof(t_symbol)));
	}
	ft_lstsort(&new_lst, sort_lst_nm);
	ft_lstiter(new_lst,show_list);
}
int	handle_64(char	*ptr,size_t size, t_inf_header info)
{
	int						ncmds;
	int						i;
	struct mach_header_64	*header;
	struct load_command		*lc;
	struct symtab_command		*sym;

	i = 0;
	header = (struct mach_header_64 *)ptr;
	if (info.swap)
		swap_header(header, info.type);
	ncmds = header->ncmds;
	lc = (void *)ptr + sizeof(*header);
	if (addr_outof_range(ptr,size,lc + sizeof(lc)))
		return (1);
	for (i = 0; i <ncmds; ++i)
	{
		if (lc->cmd == LC_SYMTAB)
		{
			sym = (struct symtab_command *) lc;
			if (addr_outof_range(ptr,size,sym + sizeof(sym)))
				return (1);
			print_output(sym->nsyms, sym->symoff, sym->stroff,ptr,size);
			break;
		}
		lc = (void *) lc + lc->cmdsize;
	}
	return (0);
}

int	handle_32(char	*ptr,size_t size, t_inf_header info)
{
	uint32_t						i;
	struct mach_header	*header;
	struct load_command		*lc;
	struct symtab_command		*sym;

	i = 0;
	header = (struct mach_header *)ptr;
	if (info.swap)
		swap_header(header,info.type);
	lc = (void *)ptr + sizeof(*header);
	if (addr_outof_range(ptr,size,lc + sizeof(lc)))
		return (1);
	i = 0;
	while (i++ < header->ncmds)
	{
if (lc->cmd == LC_SYMTAB)
		{
			sym = (struct symtab_command *) lc;
			if (addr_outof_range(ptr,size,sym + sizeof(sym)))
				return (1);
			print_output_32(sym->nsyms, sym->symoff, sym->stroff,ptr,size);
			break;
		}
		lc = (void *) lc + lc->cmdsize;
	}
	return (0);
}

int	handle_fat(char *ptr, size_t size)
{
	uint32_t						i;
	struct fat_header	*header;
	struct fat_arch		*arch;
	bool	swap;

	if (size)
	;
	swap = 0;
	header = (struct fat_header *)ptr;
	arch = (void *)header + sizeof(struct fat_header);
	i = 0 ;
	if (header->magic == FAT_CIGAM)
	{
		swap_header(header, 3);
		swap = 1;
	}
	printf("nfat_arch %d\n",header->nfat_arch);
	t_inf_header inf_header;
	while (i++ < header->nfat_arch)
	{
		if (swap)
			swap_fat_arch(arch);
		printf("fat header %d %d\n",arch->size, arch->cputype);
	if ((inf_header = get_type( ptr + arch->offset,arch->size)).error == 1)
	;
	inf_header.swap = should_swap_bytes(*(int*)ptr);
	printf("inf header %d %d\n",inf_header.type, inf_header.swap);
	if (inf_header.type == 1)
		handle_32(ptr + arch->offset,size,inf_header);
	if (inf_header.type == 2)
	handle_64(ptr + arch->offset,size,inf_header);
	
		arch++;
	}
	return (0);
}
bool addr_outof_range(void *start, size_t size, void *ptr)
{
	if (ptr >= start && ptr <= start + size)
		return (0);
	ft_putstr_fd("Error out of range\n",2);
	return (1);
}

int is_magic_64(uint32_t magic) {
	return magic == MH_MAGIC_64 || magic == MH_CIGAM_64;
}
int is_magic_32(uint32_t magic) {
	return magic == MH_MAGIC || magic == MH_CIGAM;
}
int is_magic_fat(unsigned long magic) {
	return magic == FAT_MAGIC || magic == FAT_CIGAM;
}
int is_magic_ar(char *magic) {
	if (ft_strnstr(magic, ARMAG, SARMAG))
		return (1);
	return (0);
}
int should_swap_bytes(uint32_t magic) {
	return magic == MH_CIGAM || magic == MH_CIGAM_64 || magic == FAT_CIGAM;
}


int	place_for_header(size_t size)
{
	if (size >= sizeof(struct mach_header_64))
		return (2);
	else if (size >= sizeof(struct mach_header))
		return (1);
	return (0);
}


t_inf_header is_match_header(uint32_t	magic_number, size_t size)
{
	bool	_64;
	bool	_32;
	t_inf_header inf_header;
	short	size_header;

	_64 = 0;
	_32 = 0;
	ft_bzero((void *)&inf_header, sizeof(t_inf_header));
	if ((size_header = place_for_header(size)) == 0)
	{
		return (inf_header);
	}
	if (size_header == 1)
		_32 = is_magic_32(magic_number);
	else
	{
		_32 = is_magic_32(magic_number);
		_64 = is_magic_64(magic_number);
	}
	if (_32 == 1)
		inf_header.type = 1;
	else
		inf_header.type = 2;
	return (inf_header);
}

t_inf_header	get_type(char *ptr, size_t size)
{
	t_inf_header	inf_header;
	t_inf_header	tmp;
	uint32_t	magic_number;

	magic_number = *(int *)ptr;
	ft_bzero(&inf_header, sizeof(t_inf_header));
	if (size > 0 && is_magic_fat(magic_number)) // check place
		inf_header.type = 3;
	else if (size >= SARMAG && is_magic_ar(ptr))
		inf_header.type = 4;
	else if ((tmp = is_match_header(magic_number,size)).type != 0)
		inf_header.type = tmp.type;
	else
	{
		ft_putstr_fd("Error type\n",2);
		inf_header.error = 1;
	}
	return (inf_header);
}


int	nm(char *ptr,size_t size)
{
	t_inf_header	inf_header;

	if ((inf_header = get_type(ptr,size)).error == 1)
		return (1);
	inf_header.swap = should_swap_bytes(*(int *)ptr);
	if (inf_header.type == 1)
	{
		handle_32(ptr,size, inf_header);
	}
	else if (inf_header.type == 2)
	{
		return (handle_64(ptr,size, inf_header));
	}
	else if (inf_header.type == 3)
	{
		return (handle_fat(ptr,size));
	}
	else if (inf_header.type == 4)
	{
		printf("enter handle_ar\n");
	}
	return (0);
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
	if ((ptr = mmap(0, buf.st_size, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
	{
		printf("ERROR mmap !");
		return (EXIT_FAILURE);
	}
	int i = nm(ptr,buf.st_size);
	if (munmap(ptr, buf.st_size) < 0)
	{
		printf("ERROR munmap !");
		return (EXIT_FAILURE);

	}
	if (i)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
