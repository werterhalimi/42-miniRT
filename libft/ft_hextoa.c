/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hextoa.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 18:04:18 by ncotte            #+#    #+#             */
/*   Updated: 2022/10/15 18:04:21 by ncotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char	*ft_hextoa(unsigned int u)
{
	char			*str;
	int				size;
	unsigned int	nb;

	nb = u;
	size = 1;
	while (nb / 16 != 0)
	{
		nb /= 16;
		size++;
	}
	str = ft_alloc(size + 1, sizeof (*str), NULL, ALLOC);
	if (str)
	{
		str[size] = 0;
		while (--size >= 0)
		{
			str[size] = HEXADECIMAL_FORMAT[u % 16];
			u /= 16;
		}
	}
	return (str);
}
