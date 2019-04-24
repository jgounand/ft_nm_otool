#include "../inc/ft_nm.h"

int	sort_lst_nm(void	*content, void	*content_next)
{
	t_symbol *tmp;
	t_symbol *tmp2;
	int		ret;

	tmp = content;
	tmp2 = content_next;
	ret = ft_strcmp(tmp->sym_name, tmp2->sym_name);
	return(ret > 0? 1 : 0);
}

void	show_list(t_list *lst)
{
	t_symbol	*content;

	content = lst->content;
	if (content->n_value)
	printf("0x%llx\t%c %s\n",content->n_value,content->sym_type, content->sym_name);
	else
	printf("\t\t%c %s\n",content->sym_type, content->sym_name);
}

char	give_symbole_type(uint8_t n_type)
{
	if ((n_type & N_TYPE) ==  N_UNDF)
		return ('U');
	else if ((n_type & N_TYPE) ==  N_ABS)
		return ('A');
	else if ((n_type & N_TYPE) ==  N_SECT)
		return ('T');
	else if ((n_type & N_TYPE) ==  N_PBUD)
		return ('X');
	else if ((n_type & N_TYPE) ==  N_INDR)
		return ('X');
	else
			printf("error ");
	return('0');
}

void	print_output(int nsyms, int symoff, int stroff, char *ptr)
{
	int				i;
	char			*stringtable;
	struct nlist_64	*array;
	t_list	*new_lst;
	t_symbol *new;

	array = (void *)ptr + symoff;
	stringtable =(void *) ptr + stroff;
	new_lst = NULL;
	for (i =0; i <nsyms; ++i)
	{
	if(array[i].n_type & N_STAB) {
				continue;
			}
	new = malloc(sizeof(t_symbol));
		printf("%s 0x%llx\n", stringtable + array[i].n_un.n_strx, array[i].n_value);
		new->n_value = array[i].n_value;
		new->sym_type = give_symbole_type(array[i].n_type);
		new->sym_name = stringtable + array[i].n_un.n_strx;
		new->n_value = array[i].n_value;
		if (!(array[i].n_type & N_EXT))
			new->sym_type += 40;
	ft_lstadd(&new_lst,ft_lstnew(new,sizeof(t_symbol)));
	}
	ft_lstsort(&new_lst, sort_lst_nm);
	printf("nbr node %d\n",ft_lstcmp(&new_lst));
	ft_lstiter(new_lst,show_list);
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
