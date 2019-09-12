
#include "../inc/ft_nm.h"

static char						st_set_upper(char c, struct nlist symbol)
{
	if ((symbol.n_type & N_EXT) && c != ' ')
		return (ft_toupper(c));
	return (c);
}

static char						st_find_char(struct segment_command *segment,
		unsigned int index)
{
	struct section			*sect;

	sect = (struct section *)((char *)segment
			+ sizeof(struct segment_command));
	sect += index;
	printf("index %d ,seg name %s sec name %s ",index, sect->segname, sect->sectname);
	if (!ft_strcmp(sect->sectname, SECT_BSS))
		return ('b');
	if (!ft_strcmp(sect->sectname, SECT_DATA))
		return ('d');
	if (!ft_strcmp(sect->sectname, SECT_TEXT))
		return ('t');
	return ('s');
}

static size_t get_nbr_section(size_t ncmds,struct load_command *cmd, bool swap)
{
	struct segment_command	*segment;
	unsigned int				index[2];

	index[0] = 0;
	index[1] = 0;
	while (index[0]++ < ncmds)
	{
		if (cmd->cmd == LC_SEGMENT)
		{
			segment = (struct segment_command *)cmd;
				//return(st_find_char(segment, symbol.n_sect - index[1]));
			if (swap)
				swap_segment_command(segment,0);
			index[1] += segment->nsects;
		}
		cmd = (struct load_command *)(((char *)cmd) + cmd->cmdsize);
	}
	return (index[1]);
}

static void	fil_tab_section_from_seg(struct segment_command *segment, void**ptr, size_t nsects)
{
	struct section *sect;
	struct section **tmp2;
	void *tmp;

	tmp = *ptr;
	sect = (struct section *)((char *)segment
			+ sizeof(struct segment_command));
	printf("nsects %ld\n",nsects);
	while (nsects--)
	{
		tmp = &sect;
		tmp2 = tmp;
	printf("seg name %s sec name %s tmp %p\n", (*tmp2)->segname, sect->sectname,tmp);
		tmp++;
		sect++;
	}
}

static void	fil_tab_section(t_inf_header info, void **tab, struct load_command *cmd)
{

	struct mach_header		*header;
	struct segment_command	*segment;
	size_t				index[2];

	*tab = *tab;
	index[0] = 0;
	index[1] = 0;
	header = (struct mach_header *)info.file;

	while (index[0]++ < header->ncmds)
	{
		if (cmd->cmd == LC_SEGMENT)
		{
			segment = (struct segment_command *)cmd;
				//return(st_find_char(segment, symbol.n_sect - index[1]));
			if (info.swap)
				swap_segment_command(segment,0);
			if (segment->nsects)
				fil_tab_section_from_seg(segment, (*tab) + index[1], segment->nsects);
			index[1] += segment->nsects;
		}
		cmd = (struct load_command *)(((char *)cmd) + cmd->cmdsize);
	}
	struct section **tmp2;
	tmp2 = *tab;
	printf("seg name %s sec name %s \n", (*tmp2)->segname, (*tmp2)->sectname);
	printf("sect 2 %ld\n",index[1]);
}

static char	find_type(struct nlist symbol, t_inf_header info)
{
	struct load_command			*cmd;
	struct mach_header		*header;
	struct segment_command	*segment;
	size_t					size;
	unsigned int				index[2];
	void *tab_section;

	header = (struct mach_header *)info.file;
	index[0] = 0;
	index[1] = 0;
	cmd = (struct load_command *)(((char *)info.file)
			+ sizeof(struct mach_header));
	printf("nbr nsects %ld\n",get_nbr_section(header->ncmds, cmd,info.swap));
	size = get_nbr_section(header->ncmds, cmd, info.swap);
	tab_section = malloc(sizeof(void *) * size);
	fil_tab_section(info,&tab_section,cmd);
			if (0)
				return(st_find_char(segment, symbol.n_sect - index[1]));
	
	exit(1);
	return ('s');
}

char							ft_get_type_32(struct nlist symbol, t_inf_header info)
{
	if ((symbol.n_type & N_TYPE) == N_SECT && symbol.n_sect != NO_SECT)
		return (st_set_upper(find_type(symbol, info), symbol));
	if ((symbol.n_type & N_TYPE) == N_UNDF && symbol.n_sect == NO_SECT)
	{
		if (symbol.n_value)
			return (symbol.n_type & N_EXT ? 'C' : '?');
		else
			return (st_set_upper('u', symbol));
	}
	if ((symbol.n_type & N_TYPE) == N_ABS)
		return (st_set_upper('a', symbol));
	if ((symbol.n_type & N_TYPE) == N_INDR)
		return (st_set_upper('i', symbol));
	return ('?');
}
