#include "../inc/ft_otool.h"

int	ft_show_32(struct section *sec,t_inf_header info)
{
	uint32_t	i;

	i = 0;
	ft_putstr("Contents of (__TEXT,__text) section\n");
	while (i < sec->size)
	{
		ft_show_line(sec->addr,info.file + sec->offset,i,sec->size,0);
		i += 16;
	}
	return (EXIT_SUCCESS);
}
int	handle_32_ot(t_inf_header info)
{
	uint32_t				i;
	struct mach_header	*header;
	struct load_command		*lc;

	i = 0;
	header = (struct mach_header *)info.file;
	lc = (void *)info.file + sizeof(*header);
	if (info.swap)
		swap_header(header, info.type);
	if (check_load_command(header->ncmds,header,info,0))
		return(EXIT_FAILURE);
	while (i++ < header->ncmds)
	{
		if (addr_outof_range(info, lc))
			return (EXIT_FAILURE);
		if (lc->cmd == LC_SEGMENT)
		{
			struct segment_command *seg = (void *)lc;
			struct section *sec = (void *)lc + sizeof(*seg);
			if (!ft_strcmp(seg->segname, SEG_TEXT) && !ft_strcmp(sec->sectname, SECT_TEXT))
			ft_show_32(sec,info);
		}
		lc = (void *) lc + lc->cmdsize;
	}
	return (EXIT_SUCCESS);
}
