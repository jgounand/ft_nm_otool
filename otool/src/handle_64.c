
#include "../inc/ft_otool.h"

int	ft_show_64(struct section_64 *sec,t_inf_header info)
{
	uint32_t	i;

	i = 0;

	if (addr_outof_range(info, info.file + sec->offset + sec->size))
		return (EXIT_FAILURE);
	ft_putstr("Contents of (__TEXT,__text) section\n");
	while (i < sec->size)
	{
		ft_show_line(sec->addr,info.file + sec->offset,i,sec->size,64);
		i += 16;
	}
	return (EXIT_SUCCESS);
}

int	handle_64_ot(t_inf_header info)
{
	uint32_t				i;
	struct mach_header_64	*header;
	struct load_command		*lc;

	i = 0;
	header = (struct mach_header_64 *)info.file;
	lc = (void *)info.file + sizeof(*header);
	if (info.swap)
		swap_header(header, info.type);
	if (check_load_command(header->ncmds,header,info,1))
		return(EXIT_FAILURE);
	while (i++ < header->ncmds)
	{
		if (addr_outof_range(info, lc))
			return (EXIT_FAILURE);
		if (lc->cmd == LC_SEGMENT_64)
		{
			struct segment_command_64 *seg = (void *)lc;
			struct section_64 *sec = (void *)lc + sizeof(*seg);
			if (!ft_strcmp(seg->segname, SEG_TEXT) || !ft_strcmp(sec->sectname, SECT_TEXT))
			ft_show_64(sec,info);
		}
		lc = (void *) lc + lc->cmdsize;
	}
	return (EXIT_SUCCESS);
}

