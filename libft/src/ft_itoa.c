/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgounand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 18:00:05 by jgounand          #+#    #+#             */
/*   Updated: 2019/09/17 13:09:52 by jgounand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	cp_itoa(char *s, int nega, unsigned int nb, size_t len)
{
	if (nb == 0)
		s[0] = '0';
	while (nb != 0)
	{
		s[--len] = nb % 10 + '0';
		nb /= 10;
	}
	if (nega == -1)
	{
		s[--len] = '-';
	}
}

static int	size(int tmp, int len)
{
	while (tmp)
	{
		tmp /= 10;
		len++;
	}
	return (len);
}

char		*ft_itoa(int n)
{
	unsigned int	tmp;
	int				nega;
	size_t			len;
	char			*result;

	nega = 1;
	len = 0;
	if (n < 0)
	{
		nega = -1;
		tmp = -n;
		len++;
	}
	else
		tmp = n;
	if (tmp == 0)
		len = 1;
	else
		len = size(tmp, len);
	tmp = (nega != -1) ? n : -n;
	result = ft_strnew(len);
	if (!result)
		return (NULL);
	cp_itoa(result, nega, tmp, len);
	return (result);
}

char	*ft_itoa_base(long long value, int base)
{
	long		i;
	char	*nbr;
	int		neg;

	i = 1;
	neg = 0;
	if (value < 0)
	{
		if (base == 10)
			neg = 1;
		value *= -1;
	}
	while (ft_pow(base, i) - 1 < value)
		i++;
	nbr = (char*)malloc(sizeof(nbr) * i);
	nbr[i + neg] = '\0';
	while (i-- > 0)
	{
		nbr[i + neg] = (value % base) + (value % base > 9 ? 'a' - 10 : '0');
		value = value / base;
	}
	if (neg)
		nbr[0] = '-';
	return (nbr);
}
