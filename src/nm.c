#include "../inc/ft_nm.h"

char	g_badstring[] = "bad string index";
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

char *ft_get_name_64(char type, struct nlist_64 list, t_inf_header info, void *stringtable)
{
	if (type == 'I')
	{
		if (stringtable + list.n_value < info.file || stringtable + list.n_value > info.file + info.size)
		return ("?");
		else
			return(stringtable + list.n_value);
	}
	if (stringtable + list.n_un.n_strx < info.file || stringtable + list.n_un.n_strx > info.file + info.size)
		return (g_badstring);
	else
		return (stringtable + list.n_un.n_strx);
}

t_list	*parse_symtab_64(struct nlist_64 *array, t_inf_header info,struct symtab_command *sym)
{
	uint32_t	i;
	t_list	*new_lst;
	t_symbol new;
	char	*stringtable;

	i = 0;
	new_lst = NULL;
	stringtable = info.file + sym->stroff;
	while (i < sym->nsyms)
	{
		if(array[i].n_type & N_STAB && ++i)
			continue;
		if ((new.sym_type = ft_get_type_64(array[i], info)) == 1) // => free
			return (NULL);
		new.sym_name = ft_get_name_64(new.sym_type, array[i], info, stringtable);
		new.n_value = array[i].n_value;
		new.cpu_type = 64;
		ft_lstadd(&new_lst,ft_lstnew(&new,sizeof(t_symbol)));
		i++;
	}
	return (new_lst);
}

int	create_lst_64(struct symtab_command *sym, t_inf_header info)
{
	struct nlist_64	*array;
	t_list	*new_lst;

	array = (void *)info.file + sym->symoff;
	if (addr_outof_range(info, array + sym->nsyms))
		return (EXIT_FAILURE);
	if (info.swap)
		swap_all_nlist64(array,sym);
	new_lst = parse_symtab_64(array,info,sym);
	if (new_lst)
	{
		ft_lstsort(&new_lst, sort_lst_nm);
		ft_lstiter(new_lst,show_list);
		//free
	}
	return (EXIT_SUCCESS);
}

char *ft_get_name_32(char type, struct nlist list, t_inf_header info, void *stringtable)
{
	if (type == 'I')
	{
		if (stringtable + list.n_value < info.file || stringtable + list.n_value > info.file + info.size)
		return ("?");
		else
			return(stringtable + list.n_value);
	}
	if (stringtable + list.n_un.n_strx < info.file || stringtable + list.n_un.n_strx > info.file + info.size)
		return (g_badstring);
	else
		return (stringtable + list.n_un.n_strx);
}
t_list	*parse_symtab_32(struct nlist*array, t_inf_header info,struct symtab_command *sym)
{
	uint32_t	i;
	t_list	*new_lst;
	t_symbol new;
	char	*stringtable;

	i = 0;
	new_lst = NULL;
	stringtable = info.file + sym->stroff;
	while (i < sym->nsyms)
	{
		if(array[i].n_type & N_STAB && ++i)
			continue;
		if ((new.sym_type = ft_get_type_32(array[i], info)) == 1) // => free
			return (NULL);
		new.sym_name = ft_get_name_32(new.sym_type, array[i], info, stringtable);
		new.n_value = array[i].n_value;
		new.cpu_type = 64;
		ft_lstadd(&new_lst,ft_lstnew(&new,sizeof(t_symbol)));
		i++;
	}
	return (new_lst);
}

int	create_lst_32(struct symtab_command *sym,  t_inf_header info)
{
	char			*stringtable;
	struct nlist	*array;
	t_list	*new_lst;

	array = (void *)info.file + sym->symoff;
	stringtable =(void *) info.file + sym->stroff;
	if (addr_outof_range(info, array + sym->nsyms))
		return (EXIT_FAILURE);
	if (info.swap)
		swap_all_nlist(array,sym);
	new_lst = parse_symtab_32(array,info,sym);
	if (new_lst)
	{
	ft_lstsort(&new_lst, sort_lst_nm);
	ft_lstiter(new_lst,show_list);
	}
	return (EXIT_SUCCESS);
}

int	check_load_command(uint32_t ncmds,void *header,t_inf_header info, bool _64)
{
	uint32_t	i;
	struct	load_command	*lc;
	short					modulo;

	if (_64)
	{
		lc = (void *)((struct mach_header_64 *)header) + sizeof(struct mach_header_64);
		modulo = 8;
	}
	else
	{
		lc = (void *)((struct mach_header *)header) + sizeof(struct mach_header);
		modulo = 4;
	}
	i = 0;
	while (i++ < ncmds)
	{
		 if(info.swap)
			swap_load_command(lc);
		if (addr_outof_range(info, lc) || lc->cmdsize % modulo != 0)
		{
		ft_putstr_fd("Error segment ",2);
		ft_putnbr_fd(i - 1,2);
		ft_putstr_fd("\n",2);
		return (EXIT_FAILURE);
		}
		lc = (void *) lc + lc->cmdsize;
	}
	return (EXIT_SUCCESS);
}

int	handle_64(t_inf_header info)
{
	uint32_t				i;
	struct mach_header_64	*header;
	struct load_command		*lc;

	i = 0;
	header = (struct mach_header_64 *)info.file;
	lc = (void *)info.file + sizeof(*header);
	if (info.swap)
		swap_header(header, info.type);
	if (check_load_command(header->ncmds,header,info,1))
		return(EXIT_FAILURE);
	while (i++ < header->ncmds)
	{
		if (addr_outof_range(info, lc))
			return (EXIT_FAILURE);
		if (lc->cmd == LC_SYMTAB)
			return(create_lst_64((struct symtab_command *)lc, info));
		lc = (void *) lc + lc->cmdsize;
	}
	return (EXIT_SUCCESS);
}

int	handle_32(t_inf_header info)
{
	uint32_t			i;
	struct mach_header	*header;
	struct load_command	*lc;

	i = 0;
	header = (struct mach_header *)info.file;
	lc = (void *)info.file + sizeof(*header);
	if (info.swap)
		swap_header(header,info.type);
	if (check_load_command(header->ncmds,header,info,0) == EXIT_FAILURE)
		return(EXIT_FAILURE);
	while (i++ < header->ncmds)
	{
		if (addr_outof_range(info, lc))
			return (EXIT_FAILURE);
		if (lc->cmd == LC_SYMTAB)
			return(create_lst_32((struct symtab_command *)lc, info) == EXIT_FAILURE);
		lc = (void *) lc + lc->cmdsize;
	}
	return (EXIT_SUCCESS);
}

int	position_header(struct fat_header  *header, cpu_type_t cpusearch, bool swap)
{
	uint32_t		i;
	struct fat_arch	*arch;

	arch = (void *)header + sizeof(struct fat_header);
	i = 0;
	while (i < header->nfat_arch)
	{
		if (swap)
			swap_fat_arch(arch);
		if (arch->cputype == cpusearch)
			return (i);
		arch++;
		i++;
	}
	return (-1);
}

void print_arch(struct fat_arch *arch)
{
	if (arch->cputype == CPU_TYPE_VAX)
		ft_putstr("any");
	else if (arch->cputype == CPU_TYPE_VAX)
		ft_putstr("vax");
	else if (arch->cputype == CPU_TYPE_MC680x0)
		ft_putstr("mc680x0");
	else if (arch->cputype == CPU_TYPE_I386)
		ft_putstr("i386");
	else if (arch->cputype == CPU_TYPE_X86_64)
		ft_putstr("x86_64");
	else if (arch->cputype == CPU_TYPE_HPPA)
		ft_putstr("hppa");
	else if (arch->cputype == CPU_TYPE_ARM)
		ft_putstr("arm");
	else if (arch->cputype == CPU_TYPE_MC88000)
		ft_putstr("mc88000");
	else if (arch->cputype == CPU_TYPE_SPARC)
		ft_putstr("sparc");
	else if (arch->cputype == CPU_TYPE_I860)
		ft_putstr("i860");
	else if (arch->cputype == CPU_TYPE_MC98000)
		ft_putstr("mc98000");
	else if (arch->cputype == CPU_TYPE_POWERPC)
		ft_putstr("ppc");
	else if (arch->cputype == CPU_ARCH_ABI64)
		ft_putstr("abi64");
	else if (arch->cputype == CPU_TYPE_POWERPC64)
		ft_putstr("powerpc64");
}

int	print_all_fat(t_inf_header info)
{

	uint32_t						i;
	struct fat_arch		*arch;
	struct fat_header	*header;

	header = info.file;
	i = 0;
	arch = (void *)header + sizeof(struct fat_header);
	while (i++ < header->nfat_arch)
	{
		if (addr_outof_range(info,(void *)header + arch->offset + arch->size))
			return (1);
		ft_putchar('\n');
		ft_putstr(info.filename);
		ft_putstr(" (for architecture ");
		print_arch(arch);
		ft_putstr("):\n");
		if (nm((void *)header + arch->offset,arch->size,info.filename) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		arch++;
	}
	return (EXIT_SUCCESS);
}

int	handle_fat(t_inf_header info)
{
	uint32_t						i;
	struct fat_header	*header;
	struct fat_arch		*arch;
	bool	swap;
	int index;

	header = (struct fat_header *)info.file;
	arch = (void *)header + sizeof(struct fat_header);
	swap = 0;
	i = 0 ;
	if (header->magic == FAT_CIGAM && (swap = 1))
		swap_header(header, 3);
	if (addr_outof_range(info, arch +  header->nfat_arch))
		return (EXIT_FAILURE);
	if ((index = position_header(header, CPU_TYPE_X86_64,swap)) != -1)
	{
		arch += index;
		if (addr_outof_range(info, info.file + arch->offset + arch->size))
			return (EXIT_FAILURE);
		return(nm(info.file + arch->offset, arch->size,info.filename));
	}
	print_all_fat(info);
	return (EXIT_SUCCESS);
}

bool addr_outof_range(t_inf_header info, void *ptr)
{
	if (ptr < info.file || ptr > info.file + info.size)
	{
		ft_putstr_fd("Error out of range\n",2);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
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


t_inf_header	get_type_cpu(char *ptr, size_t size)
{
	t_inf_header	inf_header;
	uint32_t	magic_number;

	magic_number = *(int *)ptr;
	ft_bzero(&inf_header, sizeof(t_inf_header));
	if (size >= sizeof(struct ar_hdr) && is_magic_ar(ptr))
		inf_header.type = 4;
	else if (size >= sizeof(struct fat_header) && is_magic_fat(magic_number))
		inf_header.type = 3;
	else if (size > sizeof(struct mach_header_64) && is_magic_64(magic_number))
		inf_header.type = 2;
	else if (size > sizeof(struct mach_header) && is_magic_32(magic_number))
		inf_header.type = 1;
	else
		inf_header.error = 1;
	return (inf_header);
}

static void	print_archive_file_name(char *filename, char *symbol)
{
	write(1, "\n", 1);
	write(1, filename, ft_strlen(filename));
	write(1, "(", 1);
	write(1, symbol, ft_strlen(symbol));
	write(1, "):\n", 3);
}

int	handle_ar(t_inf_header info)
{
struct ar_hdr	*header;
	char			*str;
	size_t			len;
	void *tmp;

tmp = info.file;
	tmp += SARMAG;
	header = (struct ar_hdr *)tmp;
	tmp += ft_atoi(header->ar_size) + sizeof(struct ar_hdr);
	while (tmp)
	{
		header = (struct ar_hdr *)tmp;
		if (ft_atoi(header->ar_size) <= 0)
			return (EXIT_FAILURE);
		str = tmp + sizeof(struct ar_hdr);
		if (tmp + (ft_atoi(header->ar_size) + sizeof(struct ar_hdr)) > tmp + info.size)
			return (EXIT_FAILURE);
		print_archive_file_name(info.filename, str);
		len = ft_strlen(str);
		while (!str[len++])
			;
		if (nm(tmp + sizeof(struct ar_hdr) + len - 1, info.file  - (tmp +sizeof(struct ar_hdr) + len - 1) + info.size, info.filename) != 0)
			return (EXIT_FAILURE);
		tmp += ft_atoi(header->ar_size) + sizeof(struct ar_hdr);
	}
		return (EXIT_SUCCESS);
}

int	nm(char *ptr,size_t size,char *av)
{
	t_inf_header	inf_header;

	if ((inf_header = get_type_cpu(ptr,size)).error == 1)
		return (EXIT_FAILURE);
	inf_header.swap = should_swap_bytes(*(int *)ptr);
	inf_header.file = ptr;
	inf_header.size = size;
	inf_header.filename = av;
	if (inf_header.type == 1)
		return(handle_32(inf_header));
	else if (inf_header.type == 2)
		return (handle_64(inf_header));
	else if (inf_header.type == 3)
		return (handle_fat(inf_header));
	else if (inf_header.type == 4)
		return(handle_ar(inf_header));
	return (EXIT_FAILURE);
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
	if (fstat(fd,&buf) < 0)
	{
		return (EXIT_FAILURE);
	}
	if ((ptr = mmap(0, buf.st_size, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
	{
		printf("ERROR mmap !");
		return (EXIT_FAILURE);
	}
	int i = nm(ptr,buf.st_size,av[1]);
	if (munmap(ptr, buf.st_size) < 0)
	{
		printf("ERROR munmap !");
		return (EXIT_FAILURE);

	}
	return (i);
}
