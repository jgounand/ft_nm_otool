/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgounand <joris@gounand.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 16:38:38 by jgounand          #+#    #+#             */
/*   Updated: 2019/09/17 12:45:29 by jgounand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_otool.h"

int		should_swap_bytes(uint32_t magic)
{
	return (magic == MH_CIGAM || magic == MH_CIGAM_64 || magic == FAT_CIGAM);
}

int		check_load_command(uint32_t ncmds, void *header, t_inf_header info,
		bool type64)
{
	uint32_t			i;
	struct load_command	*lc;
	short				modulo;

	if (type64 && (modulo = 8))
		lc = (void *)((struct mach_header_64 *)header) +
			sizeof(struct mach_header_64);
	else if ((modulo = 4))
		lc = (void *)((struct mach_header *)header) +
			sizeof(struct mach_header);
	i = 0;
	while (i++ < ncmds)
	{
		if (info.swap)
			swap_load_command(lc);
		if (addr_outof_range(info, lc) || lc->cmdsize % modulo != 0)
		{
			ft_putstr_fd("Error segment ", 2);
			ft_putnbr_fd(i - 1, 2);
			ft_putstr_fd("\n", 2);
			return (EXIT_FAILURE);
		}
		lc = (void *)lc + lc->cmdsize;
	}
	return (EXIT_SUCCESS);
}

bool	addr_outof_range(t_inf_header info, void *ptr)
{
	if (ptr < info.file || ptr > info.file + info.size)
	{
		ft_putstr_fd("Error out of range\n", 2);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
