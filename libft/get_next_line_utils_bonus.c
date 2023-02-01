/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 10:01:08 by ncotte            #+#    #+#             */
/*   Updated: 2022/10/17 10:01:36 by ncotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	gnl_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (s)
		while (s[i])
			i++;
	return (i);
}

void	gnl_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i <= n)
		*(unsigned char *)(s + i++) = 0;
}

int	gnl_strchr(const char *s, int c)
{
	int		i;
	char	cc;

	cc = (char)c;
	i = 0;
	while (s[i] && s[i] != cc)
		i++;
	if (s[i] == cc)
		return (i);
	return (-1);
}

char	*gnl_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	size;
	int		i;
	int		j;

	size = gnl_strlen(s1) + gnl_strlen(s2);
	if (!size)
		return (NULL);
	str = ft_calloc(size + 1, sizeof (char));
	if (str)
	{
		i = 0;
		j = 0;
		if (s1)
			while (s1[i])
				str[j++] = s1[i++];
		i = 0;
		while (s2[i])
			str[j++] = s2[i++];
		str[j] = 0;
	}
	return (str);
}
