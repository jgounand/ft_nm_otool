/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgounand <joris@gounand.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 16:16:50 by jgounand          #+#    #+#             */
/*   Updated: 2019/09/17 12:15:40 by jgounand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_otool.h"

void	swap_header(void *header, short type)
{
	struct mach_header		*type32;
	struct mach_header_64	*type64;
	struct fat_header		*fat;

	if (type == 1)
	{
		type32 = header;
		type32->magic = __builtin_bswap32(type32->magic);
		type32->ncmds = __builtin_bswap32(type32->ncmds);
		type32->sizeofcmds = __builtin_bswap32(type32->sizeofcmds);
	}
	else if (type == 2)
	{
		type64 = header;
		type64->magic = __builtin_bswap32(type64->magic);
		type64->ncmds = __builtin_bswap32(type64->ncmds);
		type64->sizeofcmds = __builtin_bswap32(type64->sizeofcmds);
	}
	else if (type == 3)
	{
		fat = header;
		fat->magic = __builtin_bswap32(fat->magic);
		fat->nfat_arch = __builtin_bswap32(fat->nfat_arch);
	}
}

void	swap_fat_arch(struct fat_arch *arch)
{
	arch->cputype = __builtin_bswap32(arch->cputype);
	arch->cpusubtype = __builtin_bswap32(arch->cpusubtype);
	arch->offset = __builtin_bswap32(arch->offset);
	arch->size = __builtin_bswap32(arch->size);
	arch->align = __builtin_bswap32(arch->align);
}

void	swap_load_command(struct load_command *lc)
{
	lc->cmd = __builtin_bswap32(lc->cmd);
	lc->cmdsize = __builtin_bswap32(lc->cmdsize);
}

void	swap_segment_command(void *segment, bool type_64)
{
	struct segment_command_64	*type64;
	struct segment_command		*type32;

	if (type_64)
	{
		type64 = segment;
		type64->nsects = __builtin_bswap32(type64->nsects);
	}
	else
	{
		type32 = segment;
		type32->nsects = __builtin_bswap32(type32->nsects);
	}
}

void	swap_section(void *section, bool type)
{
	struct section_64	*type64;
	struct section		*type32;

	if (type)
	{
		type64 = section;
		type64->offset = __builtin_bswap32(type64->offset);
		type64->size = __builtin_bswap32(type64->size);
	}
	else
	{
		type32 = section;
		type32->offset = __builtin_bswap32(type32->offset);
		type32->size = __builtin_bswap32(type32->size);
	}
}
