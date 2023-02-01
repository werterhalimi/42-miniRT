/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uitoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 18:04:33 by ncotte            #+#    #+#             */
/*   Updated: 2022/10/15 18:05:11 by ncotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char	*ft_uitoa(unsigned int u)
{
	char			*str;
	int				size;
	unsigned int	nb;

	nb = u;
	size = 1;
	while (nb / 10 != 0)
	{
		nb /= 10;
		size++;
	}
	str = ft_calloc(size + 1, sizeof (*str));
	if (str)
	{
		str[size] = 0;
		while (--size >= 0)
		{
			str[size] = u % 10 + '0';
			u /= 10;
		}
	}
	return (str);
}
