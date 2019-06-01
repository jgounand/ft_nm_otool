
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

void	swap_load_command(struct load_command *lc)
{
	lc->cmd = __builtin_bswap32(lc->cmd);
	lc->cmdsize = __builtin_bswap32(lc->cmdsize);
}
void	swap_symtab_command(struct symtab_command *sym)
{
	sym->cmd = __builtin_bswap32(sym->cmd);
	sym->cmdsize = __builtin_bswap32(sym->cmdsize);
	sym->symoff = __builtin_bswap32(sym->symoff);
	sym->nsyms = __builtin_bswap32(sym->nsyms);
	sym->stroff = __builtin_bswap32(sym->stroff);
	sym->strsize = __builtin_bswap32(sym->strsize);
}

void	swap_nlist(void *ptr, bool type_64)
{
	struct nlist_64	*_64;
	struct nlist	*_32;

	if (type_64)
	{
		_64 = ptr;
		_64->n_un.n_strx = __builtin_bswap32(_64->n_un.n_strx);
		_64->n_desc = __builtin_bswap16(_64->n_desc);
		_64->n_value = __builtin_bswap64(_64->n_value);
	}
	else
	{
		_32 = ptr;
		_32->n_un.n_strx = __builtin_bswap32(_32->n_un.n_strx);
		_32->n_desc = __builtin_bswap16(_32->n_desc);
		_32->n_value = __builtin_bswap32(_32->n_value);

	}
}

void	swap_segment_command(void *segment, bool type_64)
{
	struct segment_command_64 *_64;
	struct segment_command		*_32;

	if (type_64)
	{
	_64 = segment;
	//	_64->cmd = __builtin_bswap32(_64->cmd);
	//	_64->cmdsize = __builtin_bswap32(_64->cmdsize);
		_64->nsects = __builtin_bswap32(_64->nsects);
	}
	else
	{
		_32 = segment;
	//	_32->cmd = __builtin_bswap32(_32->cmd);
	//	_32->cmdsize = __builtin_bswap32(_32->cmdsize);
		_32->nsects = __builtin_bswap32(_32->nsects);
	}
}
