#include "../inc/ft_nm.h"

static char *ft_get_name_32(char type, struct nlist list, t_inf_header info, void *stringtable)
{
	if (type == 'I')
	{
		if (stringtable + list.n_value < info.file || stringtable + list.n_value > info.file + info.size)
		return ("?");
		else
			return(stringtable + list.n_value);
	}
	if (stringtable + list.n_un.n_strx < info.file || stringtable + list.n_un.n_strx > info.file + info.size)
		return ("bad string index");
	else
		return (stringtable + list.n_un.n_strx);
}
static t_list	*parse_symtab_32(struct nlist*array, t_inf_header info,struct symtab_command *sym)
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
		printf("name :%s\n",new.sym_name);
		new.n_value = array[i].n_value;
		new.cpu_type = 32;
		ft_lstadd(&new_lst,ft_lstnew(&new,sizeof(t_symbol)));
		i++;
	}
	return (new_lst);
}

static int	create_lst_32(struct symtab_command *sym,  t_inf_header info)
{
	char			*stringtable;
	struct nlist	*array;
	t_list	*new_lst;

	if (info.swap)
		swap_symtab_command(sym);
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

int	handle_32(t_inf_header info)
{
	uint32_t			i;
	struct mach_header	*header;
	struct load_command	*lc;

	i = 0;
	header = (struct mach_header *)info.file;
	printf("struct :%p swap %d\n",header, info.swap);
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


