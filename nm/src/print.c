#include "../inc/ft_nm.h"

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

static void	print_n_value(t_symbol *sym, short type_cpu)
{
	char string[17];
	char	*n_value_string;
	
	string[16] = '\0';
	if (sym->sym_type == 'u' || sym->sym_type == 'U')
	//if (sym->sym_type == 'u' || sym->sym_type == 'U' || sym->sym_type == 'I' || sym->sym_type == 'i')
		ft_memset(string, ' ',16);
	else
	{
		ft_memset(string, '0',15);

		n_value_string = ft_itoa_base(sym->n_value,16);
		ft_memcpy(string + ft_strlen(string) - ft_strlen(n_value_string) + 1, n_value_string, ft_strlen(n_value_string));
		free(n_value_string);
	}
	if (type_cpu == 32)
	{
		ft_putstr(string + 8);
	}
	else
		ft_putstr(string);
	ft_putchar(' ');
}


void	show_list(t_list *lst)
{
	t_symbol	*content;

	content = lst->content;
		print_n_value(content,content->cpu_type);
		ft_putchar(content->sym_type);
		ft_putchar(' ');
		ft_putstr(content->sym_name);
		if (content->sym_type == 'I' && content->n_value_name)
		{
			ft_putstr(" (indirect for ");
			ft_putstr(content->n_value_name);
			ft_putchar(')');
		}
		ft_putchar('\n');
}
