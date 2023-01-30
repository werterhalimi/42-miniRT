/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 17:19:19 by ncotte            #+#    #+#             */
/*   Updated: 2022/10/12 13:59:26 by ncotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/// @brief Recursively write nb into str
static void	ft_rec_itoa(char *str, int nb, int i)
{
	if ((nb > 9) || (nb < -9))
		ft_rec_itoa(str, nb / 10, i - 1);
	else if ((nb < 0) && (nb > -10))
		str[0] = '-';
	if (nb < 0)
		str[i] = nb % 10 * (-1) + '0';
	else
		str[i] = nb % 10 + '0';
}

char	*ft_itoa(int n)
{
	int		size;
	char	*str;
	int		nb;

	nb = n;
	size = 1;
	if (nb < 0)
		size++;
	while (nb / 10 != 0)
	{
		nb /= 10;
		size++;
	}
	str = malloc(sizeof (*str) * (size + 1));
	if (str)
	{
		ft_rec_itoa(str, n, size - 1);
		str[size] = 0;
	}
	return (str);
}
