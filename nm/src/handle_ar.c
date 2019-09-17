/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_ar.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgounand <joris@gounand.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 14:17:05 by jgounand          #+#    #+#             */
/*   Updated: 2019/09/17 18:53:15 by jgounand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_nm.h"

static void	print_archive_file_name(char *filename, char *symbol)
{
	write(1, "\n", 1);
	write(1, filename, ft_strlen(filename));
	write(1, "(", 1);
	write(1, symbol, ft_strlen(symbol));
	write(1, "):", 3);
}

int			handle_ar(t_inf_header *info)
{
	struct ar_hdr	*head;
	char			*str;
	size_t			len;
	void			*tmp;

	head = (struct ar_hdr *)(info->file + SARMAG);
	tmp = info->file + SARMAG + ft_atoi(head->ar_size) + sizeof(*head);
	while (tmp)
	{
		head = (struct ar_hdr *)tmp;
		if (ft_atoi(head->ar_size) <= 0)
			return (EXIT_FAILURE);
		str = tmp + sizeof(struct ar_hdr);
		if (tmp + (ft_atoi(head->ar_size) + sizeof(*head)) > tmp + info->size)
			return (EXIT_FAILURE);
		print_archive_file_name(info->filename, str);
		ft_putchar('\n');
		len = ft_strlen(str);
		while (!str[len++])
			;
		if (nm(tmp + sizeof(struct ar_hdr) + len - 1, info->file -
		(tmp + sizeof(struct ar_hdr) + len - 1) + info->size, info->filename))
			return (EXIT_FAILURE);
		tmp += ft_atoi(head->ar_size) + sizeof(struct ar_hdr);
	}
	return (EXIT_SUCCESS);
}
