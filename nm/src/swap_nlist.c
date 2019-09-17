/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_nlist.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgounand <joris@gounand.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 15:39:42 by jgounand          #+#    #+#             */
/*   Updated: 2019/09/17 15:45:40 by jgounand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_nm.h"

static void	swap_nlist(void **ptr, bool type_64)
{
	struct nlist_64	*type64;
	struct nlist	*type32;

	if (type_64)
	{
		type64 = *ptr;
		type64->n_un.n_strx = __builtin_bswap32(type64->n_un.n_strx);
		type64->n_desc = __builtin_bswap16(type64->n_desc);
		type64->n_value = __builtin_bswap64(type64->n_value);
	}
	else
	{
		type32 = *ptr;
		type32->n_un.n_strx = __builtin_bswap32(type32->n_un.n_strx);
		type32->n_desc = __builtin_bswap16(type32->n_desc);
		type32->n_value = __builtin_bswap32(type32->n_value);
	}
}

void		swap_all_nlist64(struct nlist_64 *array, struct symtab_command *sym)
{
	size_t	i;

	i = 0;
	while (i < sym->nsyms)
	{
		swap_nlist((void **)&array, 1);
		array++;
		i++;
	}
}

void		swap_all_nlist(struct nlist *array, struct symtab_command *sym)
{
	size_t	i;

	i = 0;
	while (i < sym->nsyms)
	{
		swap_nlist((void **)&array, 0);
		array++;
		i++;
	}
}
