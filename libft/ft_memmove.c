/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 16:02:50 by ncotte            #+#    #+#             */
/*   Updated: 2022/10/12 15:00:43 by ncotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	int	i;

	if (!dst && !src)
		return (NULL);
	i = (int)len;
	if (dst > src)
		while (--i >= 0)
			*(char *)(dst + i) = *(char *)(src + i);
	else
	{
		i = -1;
		while (++i < (int)len)
			*(char *)(dst + i) = *(char *)(src + i);
	}	
	return (dst);
}
