#include "../inc/ft_nm.h"

static int is_magic_64(uint32_t magic) {
	return magic == MH_MAGIC_64 || magic == MH_CIGAM_64;
}

static int is_magic_32(uint32_t magic) {
	return magic == MH_MAGIC || magic == MH_CIGAM;
}

static int is_magic_fat(unsigned long magic) {
	return magic == FAT_MAGIC || magic == FAT_CIGAM;
}

static int is_magic_ar(char *magic) {
	if (ft_strnstr(magic, ARMAG, SARMAG))
		return (1);
	return (0);
}

int should_swap_bytes(uint32_t magic) {
	return magic == MH_CIGAM || magic == MH_CIGAM_64 || magic == FAT_CIGAM;
}

t_inf_header	get_type_cpu(char *ptr, size_t size)
{
	t_inf_header	inf_header;
	uint32_t	magic_number;

	magic_number = *(int *)ptr;
	ft_bzero(&inf_header, sizeof(t_inf_header));
	if (size >= sizeof(struct ar_hdr) && is_magic_ar(ptr))
		inf_header.type = 4;
	else if (size >= sizeof(struct fat_header) && is_magic_fat(magic_number))
		inf_header.type = 3;
	else if (size > sizeof(struct mach_header_64) && is_magic_64(magic_number))
		inf_header.type = 2;
	else if (size > sizeof(struct mach_header) && is_magic_32(magic_number))
		inf_header.type = 1;
	else
		inf_header.error = 1;
	if (!inf_header.error)
		inf_header.swap = should_swap_bytes(magic_number);
	return (inf_header);
}
