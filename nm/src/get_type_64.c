/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_type_64.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgounand <joris@gounand.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 13:52:45 by jgounand          #+#    #+#             */
/*   Updated: 2019/09/17 18:04:13 by jgounand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_nm.h"

static size_t	get_nbr_section(size_t ncmds, struct load_command *cmd,
		bool swap)
{
	struct segment_command_64	*segment;
	unsigned int				index[2];

	index[0] = 0;
	index[1] = 0;
	while (index[0]++ < ncmds)
	{
		if (cmd->cmd == LC_SEGMENT)
		{
			segment = (struct segment_command_64 *)cmd;
			if (swap)
				swap_segment_command(segment, 1);
			index[1] += segment->nsects;
		}
		cmd = (struct load_command *)(((char *)cmd) + cmd->cmdsize);
	}
	return (index[1]);
}

static void		fil_tab_section_from_seg(struct segment_command_64 *segment,
		void **ptr, size_t nsects, size_t i)
{
	struct section_64	*sect;
	struct section_64	*tmp2;
	size_t				j;

	sect = (struct section_64 *)((char *)segment
			+ sizeof(struct segment_command_64));
	j = 0;
	while (j++ < nsects)
	{
		ptr[i] = sect + j - 1;
		tmp2 = (struct section_64 *)ptr[i];
		i++;
	}
}

static void		fil_tab_section_64(t_inf_header *info, struct load_command *cmd)
{
	struct mach_header_64		*header;
	struct segment_command_64	*segment;
	size_t						index[2];

	index[0] = 0;
	index[1] = 0;
	header = (struct mach_header_64 *)info->file;
	while (index[0]++ < header->ncmds)
	{
		if (cmd->cmd == LC_SEGMENT_64)
		{
			segment = (struct segment_command_64 *)cmd;
			if (segment->nsects)
				fil_tab_section_from_seg(segment, info->tab_section,
						segment->nsects, index[1]);
			index[1] += segment->nsects;
		}
		cmd = (struct load_command *)(((char *)cmd) + cmd->cmdsize);
	}
}

static char		find_type_64(struct nlist_64 symbol, t_inf_header *info)
{
	struct load_command			*cmd;
	struct mach_header_64		*header;
	unsigned int				index[2];

	header = (struct mach_header_64 *)info->file;
	index[0] = 0;
	index[1] = 1;
	cmd = (struct load_command *)(((char *)info->file) +
			sizeof(struct mach_header_64));
	if (!info->tab_section)
	{
		info->size_section = get_nbr_section(header->ncmds, cmd, info->swap);
		info->tab_section = malloc(sizeof(void *) * info->size);
		fil_tab_section_64(info, cmd);
	}
	if (symbol.n_sect <= info->size)
		return (st_find_char_64(info->tab_section[symbol.n_sect - 1]));
	return ('s');
}

char			ft_get_type_64(struct nlist_64 symbol, t_inf_header *info)
{
	if ((symbol.n_type & N_TYPE) == N_SECT && symbol.n_sect != NO_SECT)
		return (set_upper_64(find_type_64(symbol, info), symbol));
	if ((symbol.n_type & N_TYPE) == N_UNDF && symbol.n_value && symbol.n_type
			& N_EXT)
		return ('C');
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
