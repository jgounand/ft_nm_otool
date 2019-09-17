/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_64.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgounand <joris@gounand.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 16:16:56 by jgounand          #+#    #+#             */
/*   Updated: 2019/09/17 18:31:52 by jgounand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_otool.h"

static int	ft_show_64(struct section_64 *sec, t_inf_header info)
{
	uint32_t	i;

	i = 0;
	if (info.swap)
		swap_section(sec, 1);
	if (addr_outof_range(info, info.file + sec->offset + sec->size))
		return (EXIT_FAILURE);
	ft_putstr("\nContents of (__TEXT,__text) section\n");
	while (i < sec->size)
	{
		ft_show_line(sec, info, i);
		i += 16;
	}
	return (EXIT_SUCCESS);
}

static int	handle_lc64(struct load_command *lc, t_inf_header info)
{
	struct segment_command_64	*seg;
	struct section_64			*sec;

	seg = (struct segment_command_64 *)lc;
	sec = (void *)lc + sizeof(struct segment_command_64);
	if (info.swap)
		swap_segment_command(seg, 1);
	if (!ft_strcmp(seg->segname, SEG_TEXT) ||
			!ft_strcmp(sec->sectname, SECT_TEXT))
		return (ft_show_64(sec, info));
	return (EXIT_SUCCESS);
}

int			handle_64_ot(t_inf_header info)
{
	uint32_t				i;
	struct mach_header_64	*header;
	struct load_command		*lc;

	i = 0;
	header = (struct mach_header_64 *)info.file;
	lc = (void *)info.file + sizeof(*header);
	if (info.swap)
		swap_header(header, info.type);
	if (check_load_command(header->ncmds, header, info, 1))
		return (EXIT_FAILURE);
	while (i++ < header->ncmds)
	{
		if (addr_outof_range(info, lc))
			return (EXIT_FAILURE);
		if (lc->cmd == LC_SEGMENT_64)
			if (handle_lc64(lc, info) == EXIT_FAILURE)
				return (EXIT_FAILURE);
		lc = (void *)lc + lc->cmdsize;
	}
	return (EXIT_SUCCESS);
}
