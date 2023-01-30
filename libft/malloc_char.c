/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_char.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 18:11:41 by ncotte            #+#    #+#             */
/*   Updated: 2022/10/15 18:12:12 by ncotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

char	*malloc_char(int c, int *len)
{
	char	*res;

	res = malloc(sizeof (*res) * 2);
	if (res)
	{
		*len = 1;
		res[0] = (unsigned char)c;
		res[1] = 0;
	}
	return (res);
}

char	*malloc_string(char *s, int *len)
{
	char	*res;

	if (!s)
		s = "(null)";
	res = ft_strdup(s);
	if (res)
		*len = ft_strlen(res);
	return (res);
}
