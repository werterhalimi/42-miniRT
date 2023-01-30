/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 17:15:26 by ncotte            #+#    #+#             */
/*   Updated: 2022/10/12 14:30:21 by ncotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	uc;

	if (n)
	{
		uc = (unsigned char)c;
		i = 0;
		while (*(unsigned char *)(s + i) != uc && i < (n - 1))
			i++;
		if (*(unsigned char *)(s + i) == uc)
			return ((void *)(s + i));
	}
	return (NULL);
}
