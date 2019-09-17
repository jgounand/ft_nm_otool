/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgounand <joris@gounand.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 13:37:34 by jgounand          #+#    #+#             */
/*   Updated: 2019/09/17 13:41:11 by jgounand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_nm.h"

int		check_load_command(uint32_t ncmds, void *header, t_inf_header *info,
		bool type64)
{
	uint32_t			i;
	struct load_command	*lc;
	short				modulo;

	if (type64 && (modulo = 8))
		lc = (void *)((struct mach_header_64 *)header) + sizeof(*header);
	else if ((modulo = 4))
		lc = (void *)((struct mach_header *)header) + sizeof(*header);
	i = 0;
	while (i++ < ncmds)
	{
		if (info->swap)
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

bool	addr_outof_range(t_inf_header *info, void *ptr)
{
	if (ptr < info->file || ptr > info->file + info->size)
	{
		ft_putstr_fd("Error out of range\n", 2);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
