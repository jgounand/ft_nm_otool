
#include "../inc/ft_nm.h"

static char *ft_get_name_64(char type, struct nlist_64 list, t_inf_header *info, void *stringtable)
{
	if (type == 'I')
	{
		if (stringtable + list.n_value < info->file || stringtable + list.n_value > info->file + info->size)
		return ("bad string index");
		else
			return(stringtable + list.n_value);
	}
	if (stringtable + list.n_un.n_strx < info->file || stringtable + list.n_un.n_strx > info->file + info->size)
		return ("bad string index");
	else
		return (stringtable + list.n_un.n_strx);
}

static t_list	*parse_symtab_64(struct nlist_64 *array, t_inf_header *info,struct symtab_command *sym)
{
	uint32_t	i;
	t_list	*new_lst;
	t_symbol new;
	char	*stringtable;

	i = 0;
	new_lst = NULL;
	stringtable = info->file + sym->stroff;
	while (i < sym->nsyms)
	{
		if(array[i].n_type & N_STAB && ++i)
			continue;
		if ((new.sym_type = ft_get_type_64(array[i], info)) == 1) // => free
			return (NULL);
		new.sym_name = ft_get_name_64(new.sym_type, array[i], info, stringtable);
		new.n_value = array[i].n_value;
		//printf("value = %llu\t type %c\n",new.n_value,new.sym_type);
		if (new.n_value == 1585267068851191808)
		;//	exit (4);
		new.cpu_type = 64;
		ft_lstadd(&new_lst,ft_lstnew(&new,sizeof(t_symbol)));
		i++;
	}
	return (new_lst);
}

static int	create_lst_64(struct symtab_command *sym, t_inf_header *info)
{
	struct nlist_64	*array;
	t_list	*new_lst;

	if (info->swap)
		swap_symtab_command(sym);
	array = (void *)info->file + sym->symoff;
	if (addr_outof_range(info, array + sym->nsyms))
		return (EXIT_FAILURE);
	if (info->swap)
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

int	handle_64(t_inf_header *info)
{
	uint32_t				i;
	struct mach_header_64	*header;
	struct load_command		*lc;

	i = 0;
	header = (struct mach_header_64 *)info->file;
	lc = (void *)info->file + sizeof(*header);
	if (info->swap)
		swap_header(header, info->type);
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



