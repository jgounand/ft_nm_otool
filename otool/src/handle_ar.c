/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_ar.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgounand <joris@gounand.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 10:35:53 by jgounand          #+#    #+#             */
/*   Updated: 2019/09/18 10:59:49 by jgounand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_otool.h"

static void		print_archive_file_name(char *filename, char *symbol)
{
	write(1, "\n", 1);
	write(1, filename, ft_strlen(filename));
	write(1, "(", 1);
	write(1, symbol, ft_strlen(symbol));
	write(1, "):", 3);
}

static size_t	get_len_next_ar(char *str)
{
	size_t	len;

	len = ft_strlen(str);
	while (!str[len++])
		;
	return (len);
}

int				handle_ar_ot(t_inf_header info)
{
	struct ar_hdr	*header;
	char			*str;
	size_t			len;
	void			*tmp;

	header = (struct ar_hdr *)(info.file + SARMAG);
	tmp = info.file + SARMAG + ft_atoi(header->ar_size) +
		sizeof(struct ar_hdr);
	while (tmp)
	{
		header = (struct ar_hdr *)tmp;
		str = tmp + sizeof(struct ar_hdr);
		if (addr_outof_range(info, str) || addr_outof_range(info, tmp +
				ft_atoi(header->ar_size + sizeof(*header))) ||
				ft_atoi(header->ar_size) <= 0)
			return (EXIT_FAILURE);
		print_archive_file_name(info.filename, str);
		len = get_len_next_ar(str);
		if (otool(tmp + sizeof(*header) + len - 1, info.file - (tmp +
				sizeof(*header) + len - 1) + info.size, info.filename) != 0)
			return (EXIT_FAILURE);
		tmp += ft_atoi(header->ar_size) + sizeof(struct ar_hdr);
	}
	return (EXIT_SUCCESS);
}
