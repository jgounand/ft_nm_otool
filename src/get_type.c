
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

static void	swap_all_segment(struct load_command *cmd, struct mach_header *header)
{
uint32_t	i;
struct segment_command *segment;

	i = 0;
	while (i++ < header->ncmds)
	{
		if (cmd->cmd == LC_SEGMENT_64)
		{
			segment = (struct segment_command *)cmd;
			swap_segment_command(segment,1);
		}
		cmd = (struct load_command *)(((char *)cmd) + cmd->cmdsize);
	}
}

static char	find_type(struct nlist symbol, t_inf_header info)
{
	struct load_command			*cmd;
	struct mach_header		*header;
	struct segment_command	*segment;
	unsigned int				index[2];

	header = (struct mach_header *)info.file;
	index[0] = 0;
	index[1] = 1;
	cmd = (struct load_command *)(((char *)info.file)
			+ sizeof(struct mach_header));
	if (info.swap)
		swap_all_segment(cmd,header);
	while (index[0]++ < header->ncmds)
	{
		if (cmd->cmd == LC_SEGMENT)
		{
			segment = (struct segment_command *)cmd;
			if (segment->nsects && index[1] + segment->nsects > symbol.n_sect)
				return(st_find_char(segment, symbol.n_sect - index[1]));
			index[1] += segment->nsects;
		}
		cmd = (struct load_command *)(((char *)cmd) + cmd->cmdsize);
	}
	return ('s');
}

char							ft_get_type(struct nlist symbol, t_inf_header info)
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
