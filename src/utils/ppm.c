/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ppm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 19:17:46 by shalimi           #+#    #+#             */
/*   Updated: 2023/02/24 19:29:01 by shalimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static char	*append(char *str, char a)
{
	char	*ret;
	int		len;

	len = (int)ft_strlen(str) + 1;
	ret = ft_calloc(len + 1, sizeof (char));
	ft_memcpy(ret, str, len);
	ret[len - 1] = a;
	ret[len] = 0;
	ft_free(str);
	return (ret);
}

int	read_ppm(t_texture **texture, int fd)
{
	unsigned char	*map;

	if (init_texture(fd, texture))
		return (ERROR);
	map = ft_calloc((*texture)->width * (*texture)->height * 3, sizeof (*map));
	read(fd, map, (*texture)->width * (*texture)->height * 3);
	close(fd);
	create_image(texture, map);
	ft_free(map);
	(*texture)->height -= 1;
	(*texture)->width -= 1;
	return (SUCCESS);
}

char	*remove_space(char *item)
{
	char	*ret;
	int		i;

	i = -1;
	while (item[++i])
	{
		if (item[i] == ' ')
		{
			item[i] = 0;
			break ;
		}
	}
	ret = ft_strtrim(item, "\n \t");
	if (i > 0)
		item[i] = ' ';
	return (ret);
}

void	create_image(t_texture **texture, unsigned char *map)
{
	int	i;
	int	j;
	int	y;

	(*texture)->pixels = ft_calloc((*texture)->height, \
			sizeof (*(*texture)->pixels));
	j = 0;
	i = 0;
	while (i < (*texture)->height)
	{
		y = 0;
		(*texture)->pixels[i] = ft_calloc((*texture)->width, sizeof(t_color));
		while (y < (*texture)->width)
		{
			(*texture)->pixels[i][y] = (t_color){\
				(double)map[j] / (*texture)->value, \
				(double)map[j + 1] / (*texture)->value, \
				(double)map[j + 2] / (*texture)->value};
			j += 3;
			y++;
		}
		i++;
	}
}

char	*get_header(int fd)
{
	char	*ret;
	char	*tmp;
	int		nb;

	tmp = ft_calloc(2, sizeof (char));
	ret = ft_calloc(2, sizeof (char));
	tmp[1] = 0;
	ret[1] = 0;
	nb = 0;
	while (nb < 3 && read(fd, tmp, 1) > 0)
	{
		if (*tmp == '#')
		{
			while (*tmp != '\n')
				read(fd, tmp, 1);
			read(fd, tmp, 1);
		}
		ret = append(ret, *tmp);
		if (*tmp == '\n')
			nb++;
	}
	ft_free(tmp);
	return (ret);
}
