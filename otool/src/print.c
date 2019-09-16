#include "../inc/ft_otool.h"

void print_arch(struct fat_arch *arch)
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
	else if (arch->cputype == CPU_TYPE_POWERPC)
		ft_putstr("ppc");
	else if (arch->cputype == CPU_ARCH_ABI64)
		ft_putstr("abi64");
	else if (arch->cputype == CPU_TYPE_POWERPC64)
		ft_putstr("powerpc64");
}

void				ft_printpad(char *str, bool _64)
{
	int				len;
	short	ref;

	len = ft_strlen(str);
	if (_64)
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
int	ft_show_line(size_t addr, char *buff, size_t i, size_t size,bool _64)
{
	short y;
	void *tmp2;

	y = 0;
	ft_printpad(ft_itoa_base(addr + i,16),_64);
	ft_putstr("\t");
	while (y < 16 && i < size)
	{
		tmp2 = ft_itoa_base(buff[i],16);
		if (ft_strlen(tmp2) < 2)
		{
			ft_putchar('0');
			ft_putstr( tmp2 + ft_strlen(tmp2) - 1);
		}
		else
			ft_putstr( tmp2 + ft_strlen(tmp2) - 2);
		ft_putchar(' ');
		i++;
		y++;
		ft_memdel(&tmp2);
	}
	if (i < size)
		ft_putchar('\n');
	return (EXIT_SUCCESS);
}


