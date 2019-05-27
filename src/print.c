#include "../inc/ft_nm.h"

static void	print_n_value(uint64_t n_value, short type_cpu)
{
	char string[17];
	char	*n_value_string;
	
	string[16] = '\0';
	if (!n_value)
		ft_memset(string, ' ',16);
	else
	{
		ft_memset(string, '0',15);
		n_value_string = ft_itoa_base(n_value,16);
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
		print_n_value(content->n_value,content->cpu_type);
		ft_putchar(content->sym_type);
		ft_putchar(' ');
		ft_putendl(content->sym_name);
}
