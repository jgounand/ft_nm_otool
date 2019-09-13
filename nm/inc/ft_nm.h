#ifndef FT_NM_H
# define FT_NM_H

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
	void	**tab_section;
	size_t	size_section;
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


bool addr_outof_range(t_inf_header *info, void *ptr);
char							ft_get_type_64(struct nlist_64 symbol, t_inf_header *info);
char							ft_get_type_32(struct nlist symbol, t_inf_header *info);
void	show_list(t_list *lst);

t_inf_header	get_type(char *ptr, size_t size);
int should_swap_bytes(uint32_t magic);
int	nm(char *ptr,size_t size,char *av);

void	swap_header(void *header, short type);
void	swap_fat_arch(struct fat_arch *arch);
void	swap_load_command(struct load_command *lc);
void	swap_symtab_command(struct symtab_command *sym);
void	swap_nlist(void **ptr, bool type_64);
void	swap_segment_command(void *segment, bool type_64);
void	swap_all_nlist64(struct nlist_64 *array, struct symtab_command *sym);
void	swap_all_nlist(struct nlist *array, struct symtab_command *sym);

int	sort_lst_nm(void	*content, void	*content_next);
int	check_load_command(uint32_t ncmds,void *header,t_inf_header *info, bool _64);

int	handle_32(t_inf_header *info);
int	handle_64(t_inf_header *info);
int	handle_fat(t_inf_header *info);
int	handle_ar(t_inf_header *info);


void print_arch(struct fat_arch *arch);
t_inf_header	get_type_cpu(char *ptr, size_t size);
#endif
