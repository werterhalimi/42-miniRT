/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 18:07:22 by ncotte            #+#    #+#             */
/*   Updated: 2022/10/12 14:48:15 by ncotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strdup(const char *s1)
{	
	int		len;
	char	*dup;
	int		i;

	len = (int)ft_strlen(s1) + 1;
	i = -1;
	dup = ft_calloc(1, len);
	if (dup)
		while (++i < len)
			dup[i] = s1[i];
	return (dup);
}
