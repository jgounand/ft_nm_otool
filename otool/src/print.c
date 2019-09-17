/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgounand <joris@gounand.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 11:25:04 by jgounand          #+#    #+#             */
/*   Updated: 2019/09/17 18:27:42 by jgounand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_otool.h"

static void	ft_printpad(char *str, bool type64)
{
	int		len;
	short	ref;

	len = ft_strlen(str);
	if (type64)
		ref = 16;
	else
		ref = 8;
	while (len < ref)
	{
		ft_putchar('0');
		++len;
	}
	ft_putstr(str);
	ft_memdel((void **)&str);
}

static void	show_line(size_t size, char *buff, size_t i)
{
	void	*tmp2;
	short	y;

	y = 0;
	while (y < 16 && i < size)
	{
		tmp2 = ft_itoa_base(buff[i], 16);
		if (ft_strlen(tmp2) < 2)
		{
			ft_putchar('0');
			ft_putstr(tmp2 + ft_strlen(tmp2) - 1);
		}
		else
			ft_putstr(tmp2 + ft_strlen(tmp2) - 2);
		ft_putchar(' ');
		i++;
		y++;
		ft_memdel(&tmp2);
	}
	if (i < size)
		ft_putchar('\n');
}

static void	print_arch_2(struct fat_arch *arch)
{
	if (arch->cputype == CPU_TYPE_POWERPC)
		ft_putstr("ppc");
	else if (arch->cputype == CPU_ARCH_ABI64)
		ft_putstr("abi64");
	else if (arch->cputype == CPU_TYPE_POWERPC64)
		ft_putstr("powerpc64");
}

void		print_arch(struct fat_arch *arch)
{
	if (arch->cputype == CPU_TYPE_VAX)
		ft_putstr("any");
	else if (arch->cputype == CPU_TYPE_VAX)
		ft_putstr("vax");
	else if (arch->cputype == CPU_TYPE_MC680x0)
		ft_putstr("mc680x0");
	else if (arch->cputype == CPU_TYPE_I386)
		ft_putstr("i386");
	else if (arch->cputype == CPU_TYPE_X86_64)
		ft_putstr("x86_64");
	else if (arch->cputype == CPU_TYPE_HPPA)
		ft_putstr("hppa");
	else if (arch->cputype == CPU_TYPE_ARM)
		ft_putstr("arm");
	else if (arch->cputype == CPU_TYPE_MC88000)
		ft_putstr("mc88000");
	else if (arch->cputype == CPU_TYPE_SPARC)
		ft_putstr("sparc");
	else if (arch->cputype == CPU_TYPE_I860)
		ft_putstr("i860");
	else if (arch->cputype == CPU_TYPE_MC98000)
		ft_putstr("mc98000");
	else
		print_arch_2(arch);
}

void		ft_show_line(void *section, t_inf_header info, size_t i)
{
	char	*buff;
	size_t	size;
	size_t	addr;

	if (info.type == 2)
	{
		buff = info.file + ((struct section_64 *)section)->offset;
		size = ((struct section_64 *)section)->size;
		addr = ((struct section_64 *)section)->addr + i;
	}
	else
	{
		buff = info.file + ((struct section *)section)->offset;
		size = ((struct section *)section)->size;
		addr = ((struct section *)section)->addr + i;
	}
	ft_printpad(ft_itoa_base(addr, 16), info.type == 2 ? 1 : 0);
	ft_putstr("\t");
	show_line(size, buff, i);
}
