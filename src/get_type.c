
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

static char	find_type(struct nlist symbol, void *ptr,size_t size)
{
	struct load_command			*cmd;
	struct mach_header		*header;
	struct segment_command	*segment;
	unsigned int				i;
	unsigned int				n;

	header = (struct mach_header *)ptr;
	i = 0;
	n = 0;
	cmd = (struct load_command *)(((char *)ptr)
			+ sizeof(struct mach_header));
	while (i < header->ncmds)
	{
	if (addr_outof_range(ptr,size,cmd + sizeof(cmd) - 1))
		return '1';
		if (cmd->cmd == LC_SEGMENT)
		{
			segment = (struct segment_command *)cmd;
			if (addr_outof_range(ptr,size,segment + sizeof(segment) - 1))
				return '1';
			if (n + segment->nsects > symbol.n_sect)
				return (st_find_char(segment, symbol.n_sect - n - 1));
			n += segment->nsects;
		}
		cmd = (struct load_command *)(((char *)cmd) + cmd->cmdsize);
		++i;
	}
	return ('s');
}
char							ft_get_type(struct nlist symbol, void *ptr, size_t size)
{
	if ((symbol.n_type & N_TYPE) == N_SECT)
		return (st_set_upper(find_type(symbol, ptr,size), symbol));
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
