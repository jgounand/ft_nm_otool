#include "../inc/ft_nm.h"

static char						st_set_upper_64(char c, struct nlist_64 symbol)
{
	if ((symbol.n_type & N_EXT) && c != ' ')
		return (ft_toupper(c));
	return (c);
}

static char						st_find_char_64(struct segment_command_64 *segment,
		unsigned int index)
{
	struct section_64			*sect;

	sect = (struct section_64 *)((char *)segment
			+ sizeof(struct segment_command_64));
	sect += index;
	if (!ft_strcmp(sect->sectname, SECT_BSS))
		return ('b');
	if (!ft_strcmp(sect->sectname, SECT_DATA))
		return ('d');
	if (!ft_strcmp(sect->sectname, SECT_TEXT))
		return ('t');
	return ('s');
}

static char	find_type_64(struct nlist_64 symbol, void *ptr,size_t size, t_inf_header info)
{
	struct load_command			*cmd;
	struct mach_header_64		*header;
	struct segment_command_64	*segment;
	unsigned int				i;
	unsigned int				n;
	char						c;

	header = (struct mach_header_64 *)ptr;
	i = 0;
	n = 1;
	cmd = (struct load_command *)(((char *)ptr)
			+ sizeof(struct mach_header_64));
	//printf("symbol.n_sect %d\n", symbol.n_sect);
	while (i < header->ncmds)
	{
		if (addr_outof_range(ptr,size,cmd))
			return '1';
		if (cmd->cmd == LC_SEGMENT_64)
		{
			segment = (struct segment_command_64 *)cmd;
			//printf("segment nsect %d\n cmd size %d\n",segment->nsects, segment->cmdsize);
			if (segment->nsects && (n + segment->nsects > symbol.n_sect))
			{
				c = st_find_char_64(segment, symbol.n_sect - n);

				if (info.swap)
					swap_segment_command(segment,1);
				return (c);
			}
			n += segment->nsects;
			if (info.swap)
				swap_segment_command(segment,1);
		}
		if (cmd->cmdsize % 8)
			return ('1');
		cmd = (struct load_command *)(((char *)cmd) + cmd->cmdsize);
		++i;
	}
	return ('s');
}
char							ft_get_type_64(struct nlist_64 symbol, void *ptr, size_t size,t_inf_header info)
{
	if ((symbol.n_type & N_TYPE) == N_SECT && symbol.n_sect != NO_SECT)
		return (st_set_upper_64(find_type_64(symbol, ptr, size,info), symbol));
	if ((symbol.n_type & N_TYPE) == N_UNDF && symbol.n_sect == NO_SECT)
	{
		if (symbol.n_value)
			return (symbol.n_type & N_EXT ? 'C' : '?');
		else
			return (st_set_upper_64('u', symbol));
	}
	if ((symbol.n_type & N_TYPE) == N_ABS)
		return (st_set_upper_64('a', symbol));
	if ((symbol.n_type & N_TYPE) == N_INDR)
		return (st_set_upper_64('i', symbol));
	return ('?');
}

