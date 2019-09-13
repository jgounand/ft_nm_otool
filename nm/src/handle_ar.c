#include "../inc/ft_nm.h"

static void	print_archive_file_name(char *filename, char *symbol)
{
	write(1, "\n", 1);
	write(1, filename, ft_strlen(filename));
	write(1, "(", 1);
	write(1, symbol, ft_strlen(symbol));
	write(1, "):\n", 3);
}

int	handle_ar(t_inf_header *info)
{
	struct ar_hdr	*header;
	char			*str;
	size_t			len;
	void *tmp;

	header = (struct ar_hdr *)(info->file + SARMAG);
	tmp = info->file + SARMAG + ft_atoi(header->ar_size) + sizeof(struct ar_hdr);
	while (tmp)
	{
		header = (struct ar_hdr *)tmp;
		if (ft_atoi(header->ar_size) <= 0)
			return (EXIT_FAILURE);
		str = tmp + sizeof(struct ar_hdr);
		if (tmp + (ft_atoi(header->ar_size) + sizeof(struct ar_hdr)) > tmp + info->size)
			return (EXIT_FAILURE);
		print_archive_file_name(info->filename, str);
		len = ft_strlen(str);
		while (!str[len++])
			;
		if (nm(tmp + sizeof(struct ar_hdr) + len - 1, info->file -
		(tmp +sizeof(struct ar_hdr) + len - 1) + info->size, info->filename) != 0)
			return (EXIT_FAILURE);
		tmp += ft_atoi(header->ar_size) + sizeof(struct ar_hdr);
	}
		return (EXIT_SUCCESS);
}


