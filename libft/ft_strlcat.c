/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 16:31:32 by ncotte            #+#    #+#             */
/*   Updated: 2022/10/11 13:58:38 by ncotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	dest_length;

	dest_length = ft_strlen(dst);
	if (dest_length < dstsize - 1 && dstsize > 0)
	{
		i = 0;
		j = dest_length;
		while (src[i] && dest_length + i < dstsize - 1)
			dst[j++] = src[i++];
		dst[j] = 0;
	}
	if (dest_length >= dstsize)
		dest_length = dstsize;
	return (dest_length + ft_strlen(src));
}
