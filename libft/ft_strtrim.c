/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 14:54:59 by ncotte            #+#    #+#             */
/*   Updated: 2022/10/11 15:24:17 by ncotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	int		i;
	int		start;
	int		end;

	start = 0;
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;
	end = (int)ft_strlen(s1);
	while (end > start && ft_strchr(set, s1[end - 1]))
		end--;
	str = ft_alloc(end - start + 1, sizeof (char), NULL, ALLOC);
	if (str)
	{
		i = 0;
		while (start < end)
			str[i++] = s1[start++];
		str[i] = 0;
	}
	return (str);
}
