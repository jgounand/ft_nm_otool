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
	if (!ft_strcmp(segment->segname, SEG_DATA)
			&& !ft_strcmp(sect->sectname, SECT_BSS))
		return ('b');
	if (!ft_strcmp(segment->segname, "__DATA")
			&& !ft_strcmp(sect->sectname, "__bss"))
		return ('b');
	if (!ft_strcmp(segment->segname, "__DATA")
			&& !ft_strcmp(sect->sectname, "__data"))
		return ('d');
	if (!ft_strcmp(segment->segname, "__TEXT")
			&& !ft_strcmp(sect->sectname, "__text"))
		return ('t');
	return ('s');
}

static char	find_type_64(struct nlist_64 symbol, void *ptr,size_t size)
{
	struct load_command			*cmd;
	struct mach_header_64		*header;
	struct segment_command_64	*segment;
	unsigned int				i;
	unsigned int				n;

	header = (struct mach_header_64 *)ptr;
	i = 0;
	n = 1;
	cmd = (struct load_command *)(((char *)ptr)
			+ sizeof(struct mach_header_64));
	while (i < header->ncmds)
	{
	if (addr_outof_range(ptr,size,cmd + sizeof(cmd) - 1))
		return '1';
		if (cmd->cmd == LC_SEGMENT_64)
		{
			segment = (struct segment_command_64 *)cmd;
			if (n + segment->nsects > symbol.n_sect)
				return (st_find_char_64(segment, symbol.n_sect - n));
			n += segment->nsects;
		}
		cmd = (struct load_command *)(((char *)cmd) + cmd->cmdsize);
		++i;
	}
	return ('s');
}
char							ft_get_type_64(struct nlist_64 symbol, void *ptr, size_t size)
{
	if ((symbol.n_type & N_TYPE) == N_SECT)
		return (st_set_upper_64(find_type_64(symbol, ptr, size), symbol));
	if ((symbol.n_type & N_TYPE) == N_UNDF)
	{
		if (symbol.n_value == 0)
			return (st_set_upper_64('u', symbol));
		else
			return (st_set_upper_64('c', symbol));
	}
	if ((symbol.n_type & N_TYPE) == N_ABS)
		return (st_set_upper_64('a', symbol));
	if ((symbol.n_type & N_TYPE) == N_INDR)
		return (st_set_upper_64('i', symbol));
	return ('X');
}
