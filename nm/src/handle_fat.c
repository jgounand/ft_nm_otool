/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_fat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgounand <joris@gounand.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 14:25:35 by jgounand          #+#    #+#             */
/*   Updated: 2019/09/17 14:29:21 by jgounand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_nm.h"

static int	position_header(struct fat_header *header, cpu_type_t cpusearch,
		bool swap, t_inf_header *info)
{
	uint32_t		i;
	int				found;
	struct fat_arch	*arch;

	arch = (void *)header + sizeof(struct fat_header);
	i = 0;
	found = -1;
	while (i < header->nfat_arch)
	{
		if (swap)
			swap_fat_arch(arch);
		if (addr_outof_range(info, (void *)header + arch->offset + arch->size))
			return (-2);
		if (found == -1 && arch->cputype == cpusearch)
			found = i;
		arch++;
		i++;
	}
	return (found);
}

static int	print_all_fat(t_inf_header *info)
{
	uint32_t			i;
	struct fat_arch		*arch;
	struct fat_header	*header;

	header = info->file;
	i = 0;
	arch = (void *)header + sizeof(struct fat_header);
	while (i++ < header->nfat_arch)
	{
		if (addr_outof_range(info, (void *)header + arch->offset + arch->size))
			return (1);
		ft_putchar('\n');
		ft_putstr(info->filename);
		ft_putstr(" (for architecture ");
		print_arch(arch);
		ft_putstr("):\n");
		if (nm((void *)header + arch->offset, arch->size, info->filename))
			return (EXIT_FAILURE);
		arch++;
	}
	return (EXIT_SUCCESS);
}

int			handle_fat(t_inf_header *info)
{
	uint32_t			i;
	struct fat_header	*header;
	struct fat_arch		*arch;
	int					index;

	header = (struct fat_header *)info->file;
	arch = (void *)header + sizeof(struct fat_header);
	i = 0;
	if (info->swap)
		swap_header(header, 3);
	if (addr_outof_range(info, arch + header->nfat_arch))
		return (EXIT_FAILURE);
	if ((index = position_header(header, CPU_TYPE_X86_64, info->swap, info))
			>= 0)
	{
		arch += index;
		if (addr_outof_range(info, info->file + arch->offset + arch->size))
			return (EXIT_FAILURE);
		return (nm(info->file + arch->offset, arch->size, info->filename));
	}
	else if (index == -1)
		print_all_fat(info);
	else
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
