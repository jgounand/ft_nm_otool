/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_fat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgounand <joris@gounand.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 10:42:10 by jgounand          #+#    #+#             */
/*   Updated: 2019/09/17 11:14:42 by jgounand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_otool.h"

static int	position_header(struct fat_header *header, cpu_type_t cpusearch
		, bool swap)
{
	uint32_t		i;
	struct fat_arch	*arch;

	arch = (void *)header + sizeof(struct fat_header);
	i = 0;
	while (i < header->nfat_arch)
	{
		if (swap)
			swap_fat_arch(arch);
		if (arch->cputype == cpusearch)
			return (i);
		arch++;
		i++;
	}
	return (-1);
}

static int	print_all_fat(t_inf_header info)
{
	uint32_t			i;
	struct fat_arch		*arch;
	struct fat_header	*header;

	header = info.file;
	i = 0;
	arch = (void *)header + sizeof(struct fat_header);
	while (i++ < header->nfat_arch)
	{
		if (addr_outof_range(info, (void *)header + arch->offset + arch->size))
			return (1);
		ft_putchar('\n');
		ft_putstr(info.filename);
		ft_putstr(" (for architecture ");
		print_arch(arch);
		ft_putstr("):\n");
		if (otool((void *)header + arch->offset, arch->size, info.filename)
				== EXIT_FAILURE)
			return (EXIT_FAILURE);
		arch++;
	}
	return (EXIT_SUCCESS);
}

int			handle_fat_ot(t_inf_header info)
{
	uint32_t			i;
	struct fat_header	*header;
	struct fat_arch		*arch;
	int					index;

	header = (struct fat_header *)info.file;
	arch = (void *)header + sizeof(struct fat_header);
	i = 0;
	if (info.swap)
		swap_header(header, 3);
	if (addr_outof_range(info, arch + header->nfat_arch))
		return (EXIT_FAILURE);
	if ((index = position_header(header, CPU_TYPE_X86_64, info.swap)) != -1)
	{
		arch += index;
		if (addr_outof_range(info, info.file + arch->offset + arch->size))
			return (EXIT_FAILURE);
		return (otool(info.file + arch->offset, arch->size, info.filename));
	}
	print_all_fat(info);
	return (EXIT_SUCCESS);
}
