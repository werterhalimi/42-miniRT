/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_nbr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 13:00:22 by ncotte            #+#    #+#             */
/*   Updated: 2022/10/15 13:00:27 by ncotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

char	*malloc_pointer(void *p, int *len)
{
	char			*res;
	unsigned long	nb;
	int				i;

	nb = (unsigned long)p;
	i = 3;
	while (nb / 16 != 0 && i++)
		nb /= 16;
	res = malloc(sizeof (*res) * (i + 1));
	if (res)
	{
		nb = (unsigned long)p;
		ft_bzero(res, i + 1);
		*len = i;
		while (--i >= 2)
		{
			res[i] = HEXADECIMAL_FORMAT[nb % 16];
			nb /= 16;
		}
		res[0] = '0';
		res[1] = 'x';
	}
	return (res);
}

char	*malloc_signed(int i, int *len)
{
	char	*res;

	res = ft_itoa(i);
	if (res)
		*len = ft_strlen(res);
	return (res);
}

char	*malloc_unsigned(unsigned int u, int *len)
{
	char	*res;

	res = ft_uitoa(u);
	if (res)
		*len = ft_strlen(res);
	return (res);
}

char	*malloc_hex(char format, unsigned int x, int *len)
{
	char	*res;
	int		i;

	i = -1;
	res = ft_hextoa(x);
	if (res)
	{
		*len = ft_strlen(res);
		if (format == 'X')
			while (res[++i])
				res[i] = ft_toupper(res[i]);
	}
	return (res);
}
