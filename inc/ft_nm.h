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

# include "../libft/inc/libft.h"
# include <ar.h>

typedef struct s_inf_header
{
	short	type;
	bool	swap;
	bool	cpu;
	bool	error;
}		t_inf_header;

typedef struct s_symbol
{	
	char	*sym_name;
	char	sym_type;
	uint64_t n_value;
}		t_symbol;

bool addr_outof_range(void *start, size_t size, void *ptr);
#endif
