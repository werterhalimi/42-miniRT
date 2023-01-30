/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 17:33:14 by ncotte            #+#    #+#             */
/*   Updated: 2022/10/12 14:33:10 by ncotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	j;
	int		i;

	i = 0;
	j = 0;
	while (haystack[j + i] && needle[i] && (j + i) < len)
	{
		if (haystack[j + i] == needle[i])
			i++;
		else
		{
			i = 0;
			j++;
		}
	}
	if (needle[i])
		return (NULL);
	return ((char *)(haystack + j));
}
