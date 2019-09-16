#ifndef FT_OTOOL_H
# define FT_OTOOL_H
#include <stdbool.h>
#include <sys/mman.h>
#include <mach-o/loader.h>
#include <mach-o/nlist.h>
#include <mach-o/fat.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <mach-o/ranlib.h>

# include "../libft/inc/libft.h"
# include <ar.h>

typedef struct s_inf_header
{
	short	type;
	bool	swap;
	bool	cpu;
	bool	error;
	void	*file;
	size_t	size;
	char	*filename;
}		t_inf_header;

typedef struct s_symbol
{	
	char	*sym_name;
	char	*n_value_name;
	char	sym_type;
	uint64_t n_value;
	short	cpu_type;
	char	more[256];
}		t_symbol;


int	handle_64_ot(t_inf_header info);


int	check_load_command(uint32_t ncmds,void *header,t_inf_header info, bool _64);
bool addr_outof_range(t_inf_header info, void *ptr);

int	ft_show_line(size_t addr, char *buff, size_t i, size_t size,bool _64);

void	swap_header(void *header, short type);
void	swap_load_command(struct load_command *lc);

int should_swap_bytes(uint32_t magic);
t_inf_header	get_type_cpu(char *ptr, size_t size);
void				ft_printpad(char *str, bool _64);
void print_arch(struct fat_arch *arch);
int	handle_32_ot(t_inf_header info);
int	handle_fat_ot(t_inf_header info);
int	handle_ar_ot(t_inf_header info);
int	otool(char *ptr,size_t size,char *av);
void	swap_fat_arch(struct fat_arch *arch);
void	swap_segment_command(void *segment, bool type_64);
void	swap_symtab_command(struct symtab_command *sym);
void	swap_section(void *section, bool type);
#endif
