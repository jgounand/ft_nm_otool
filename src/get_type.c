
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
	//printf("seg name %s sec name %s\n",sect->segname, sect->sectname);
	if (!ft_strcmp(sect->sectname, SECT_BSS))
		return ('b');
	if (!ft_strcmp(sect->sectname, SECT_DATA))
		return ('d');
	if (!ft_strcmp(sect->sectname, SECT_TEXT))
		return ('t');
	return ('s');
}

/**
* Find the type from the number segment give on symbole
**/
static char	find_type(struct nlist symbol, void *ptr,size_t size,t_inf_header info)
{
	struct load_command			*cmd;
	struct mach_header		*header;
	struct segment_command	*segment;
	unsigned int				i;
	unsigned int				n;
	char						ret;

	header = (struct mach_header *)ptr;
	i = 0;
	n = 1;
	cmd = (struct load_command *)(((char *)ptr)
			+ sizeof(struct mach_header));
		if (size)
			;
	//printf("n_sect %d\n",symbol.n_sect);
	while (i < header->ncmds)
	{
		if (cmd->cmd == LC_SEGMENT)
		{
			segment = (struct segment_command *)cmd;
		if (info.swap)
			swap_segment_command(segment, 0);
			//printf("segment nsect %d\n cmd size %d\n",segment->nsects, segment->cmdsize);
				if (segment->nsects && n + segment->nsects > symbol.n_sect)
			{
			ret = st_find_char(segment, symbol.n_sect - n);
		if (info.swap)
			swap_segment_command(segment, 0);
				return (ret);
			}
			n += segment->nsects;
		if (info.swap)
			swap_segment_command(segment, 0);
		}
		cmd = (struct load_command *)(((char *)cmd) + cmd->cmdsize);
		++i;
	}
	return ('s');
}
char							ft_get_type(struct nlist symbol, void *ptr, size_t size, t_inf_header info)
{
	if ((symbol.n_type & N_TYPE) == N_SECT)
		return (st_set_upper(find_type(symbol, ptr,size,info), symbol));
	if ((symbol.n_type & N_TYPE) == N_UNDF)
	{
		if (symbol.n_value == 0)
			return (st_set_upper('u', symbol));
		else
			return (st_set_upper('c', symbol));
	}
	if ((symbol.n_type & N_TYPE) == N_ABS)
		return (st_set_upper('a', symbol));
	if ((symbol.n_type & N_TYPE) == N_INDR)
		return (st_set_upper('i', symbol));
	return ('X');
}
