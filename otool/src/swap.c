/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgounand <joris@gounand.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 16:16:50 by jgounand          #+#    #+#             */
/*   Updated: 2019/09/16 16:19:03 by jgounand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_otool.h"
void	swap_header(void *header, short type)
{
	struct mach_header	*_32;
	struct mach_header_64	*_64;
	struct fat_header		*fat;
	
	if (type == 1)
	{
		_32 = header;
		_32->magic = __builtin_bswap32(_32->magic);
		_32->ncmds = __builtin_bswap32(_32->ncmds);
		_32->sizeofcmds = __builtin_bswap32(_32->sizeofcmds);
	}
	else if (type == 2)
	{
		_64 = header;
		_64->magic = __builtin_bswap32(_64->magic);
		_64->ncmds = __builtin_bswap32(_64->ncmds);
		_64->sizeofcmds = __builtin_bswap32(_64->sizeofcmds);
	}
	else if (type == 3)
	{
		fat = header;
		fat->magic = __builtin_bswap32(fat->magic);
		fat->nfat_arch = __builtin_bswap32(fat->nfat_arch);
	}
	else if (type == 4)
	{

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
	struct segment_command_64 *_64;
	struct segment_command		*_32;

	if (type_64)
	{
	_64 = segment;
		_64->nsects = __builtin_bswap32(_64->nsects);
	}
	else
	{
		_32 = segment;
		_32->nsects = __builtin_bswap32(_32->nsects);
	}
}
void	swap_section(void *section, bool type)
{

	struct section_64	*_64;
	struct section		*_32;

	if (type)
	{
		_64 = section;
		_64->offset = __builtin_bswap32(_64->offset);
		_64->size = __builtin_bswap32(_64->size);
	}
	else
	{
		_32 = section;
		_32->offset = __builtin_bswap32(_32->offset);
		_32->size = __builtin_bswap32(_32->size);

	}
}
