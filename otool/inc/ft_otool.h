/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_otool.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgounand <joris@gounand.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 13:05:05 by jgounand          #+#    #+#             */
/*   Updated: 2019/09/18 12:22:42 by jgounand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_OTOOL_H
# define FT_OTOOL_H

# include <stdbool.h>
# include <sys/mman.h>
# include <mach-o/loader.h>
# include <mach-o/nlist.h>
# include <mach-o/fat.h>
# include <fcntl.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <mach-o/ranlib.h>

# include "../libft/inc/libft.h"
# include <ar.h>

/*
** Struct t_inf_header
** Stock the important information of the object
*/
typedef struct	s_inf_header
{
	short	type;
	bool	swap;
	bool	cpu;
	bool	error;
	void	*file;
	size_t	size;
	char	*filename;
}				t_inf_header;

/*
** otool.c
*/
int				otool(char *ptr, size_t size, char *av);
/*
** check.c
*/
int				should_swap_bytes(uint32_t magic);
int				check_load_command(uint32_t ncmds, void *header,
		t_inf_header info, bool type64);
bool			addr_outof_range(t_inf_header info, void *ptr);
/*
** handle_32.c
*/
int				handle_32_ot(t_inf_header info);
/*
** handle_64.c
*/
int				handle_64_ot(t_inf_header info);
/*
** handle_ar.c
*/
int				handle_ar_ot(t_inf_header info);
/*
** handle_fat.c
*/
int				handle_fat_ot(t_inf_header info);
/*
** is_magic_swap.c
*/
t_inf_header	get_type_cpu(char *ptr, size_t size);
/*
** print.c
*/
void			print_arch(struct fat_arch *arch);
void			ft_show_line(void *section, t_inf_header info, size_t i);
/*
** swap.c
*/
void			swap_header(void *header, short type);
void			swap_fat_arch(struct fat_arch *arch);
void			swap_load_command(struct load_command *lc);
void			swap_segment_command(void *segment, bool type_64);
void			swap_section(void *section, bool type);

#endif
