#include "../inc/ft_nm.h"

static char	set_upper_64(char c, struct nlist_64 symbol)
{
	if ((symbol.n_type & N_EXT) && c != ' ')
		return (ft_toupper(c));
	return (c);
}

static char	find_char_64(struct segment_command_64 *segment,
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

static void	swap_all_segment(struct load_command *cmd, struct mach_header_64 *header)
{
uint32_t	i;
struct segment_command_64 *segment;

	i = 0;
	while (i++ < header->ncmds)
	{
		if (cmd->cmd == LC_SEGMENT_64)
		{
			segment = (struct segment_command_64 *)cmd;
			swap_segment_command(segment,1);
		}
		cmd = (struct load_command *)(((char *)cmd) + cmd->cmdsize);
	}
}

static char	find_type_64(struct nlist_64 symbol, t_inf_header info)
{
	struct load_command			*cmd;
	struct mach_header_64		*header;
	struct segment_command_64	*segment;
	unsigned int				index[2];

	header = (struct mach_header_64 *)info.file;
	index[0] = 0;
	index[1] = 1;
	cmd = (struct load_command *)(((char *)info.file) + sizeof(*header));
	if (info.swap)
		swap_all_segment(cmd,header);
	while (index[0]++ < header->ncmds)
	{
		if (cmd->cmd == LC_SEGMENT_64)
		{
			segment = (struct segment_command_64 *)cmd;
			if (segment->nsects && (index[1] + segment->nsects > symbol.n_sect))
				return(find_char_64(segment, symbol.n_sect - index[1]));
			index[1] += segment->nsects;
		}
		cmd = (struct load_command *)(((char *)cmd) + cmd->cmdsize);
	}
	return ('s');
}

char		ft_get_type_64(struct nlist_64 symbol, t_inf_header info)
{
	if ((symbol.n_type & N_TYPE) == N_SECT && symbol.n_sect != NO_SECT)
		return (set_upper_64(find_type_64(symbol, info), symbol));
	if ((symbol.n_type & N_TYPE) == N_UNDF && symbol.n_sect == NO_SECT)
	{
		if (symbol.n_value)
			return (symbol.n_type & N_EXT ? 'C' : '?');
		else
			return (set_upper_64('u', symbol));
	}
	if ((symbol.n_type & N_TYPE) == N_ABS)
		return (set_upper_64('a', symbol));
	if ((symbol.n_type & N_TYPE) == N_INDR)
		return (set_upper_64('i', symbol));
	return ('?');
}

