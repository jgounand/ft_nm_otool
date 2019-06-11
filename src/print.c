#include "../inc/ft_nm.h"

static void	print_n_value(t_symbol *sym, short type_cpu)
{
	char string[17];
	char	*n_value_string;
	
	string[16] = '\0';
	if (sym->sym_type == 'u' || sym->sym_type == 'U' || sym->sym_type == 'I' || sym->sym_type == 'i')
		ft_memset(string, ' ',16);
	else
	{
		ft_memset(string, '0',15);

		n_value_string = ft_itoa_base(sym->n_value,16);
		ft_memcpy(string + ft_strlen(string) - ft_strlen(n_value_string) + 1, n_value_string, ft_strlen(n_value_string));
		free(n_value_string);
	}
	if (type_cpu == 32)
		ft_putstr(string + 8);
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
		if (content->sym_type == 'I')
		{
			ft_putstr(" (indirect for ");
			ft_putstr(content->n_value_name);
			ft_putchar(')');
		}
		ft_putchar('\n');
}
