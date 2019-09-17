/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgounand <joris@gounand.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 15:32:57 by jgounand          #+#    #+#             */
/*   Updated: 2019/09/17 15:40:51 by jgounand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_nm.h"

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

void	swap_symtab_command(struct symtab_command *sym)
{
	sym->symoff = __builtin_bswap32(sym->symoff);
	sym->nsyms = __builtin_bswap32(sym->nsyms);
	sym->stroff = __builtin_bswap32(sym->stroff);
	sym->strsize = __builtin_bswap32(sym->strsize);
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
