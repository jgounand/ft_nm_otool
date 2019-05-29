
#include "../inc/ft_nm.h"
void	swap_header(void *header, short type)
{
	struct mach_header	*_32;
	struct mach_header_64	*_64;
	struct fat_header		*fat;
	
	if (type == 1)
	{
		_32 = header;
		_32->magic = __builtin_bswap32(_32->magic);
		_32->ncmds = __builtin_bswap32(_32->ncmds);
	}
	else if (type == 2)
	{
		_64 = header;
		_64->magic = __builtin_bswap32(_64->magic);
		_64->ncmds = __builtin_bswap32(_64->ncmds);
	}
	else if (type == 3)
	{
		fat = header;
		fat->magic = __builtin_bswap32(fat->magic);
		fat->nfat_arch = __builtin_bswap32(fat->nfat_arch);
	}
	else if (type == 4)
	{

	}
}

void	swap_fat_arch(struct fat_arch *arch)
{
	arch->cputype = __builtin_bswap32(arch->cputype);
	arch->cpusubtype = __builtin_bswap32(arch->cpusubtype);
	arch->offset = __builtin_bswap32(arch->offset);
	arch->size = __builtin_bswap32(arch->size);
	arch->align = __builtin_bswap32(arch->align);
}
