/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 14:03:02 by ncotte            #+#    #+#             */
/*   Updated: 2022/10/12 15:54:50 by ncotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	j;
	char	*str;

	str = (char *)ft_calloc(len + 1, sizeof (*s));
	if (str)
	{
		i = 0;
		j = 0;
		while (s[i])
		{
			if (i >= start && j < len)
				str[j++] = s[i];
			i++;
		}
		str[j] = 0;
	}
	return (str);
}
