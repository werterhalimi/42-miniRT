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
	if (!ret)
		return (NULL);
	ft_memcpy(ret, str, len);
	ret[len - 1] = a;
	ret[len] = 0;
	ft_free(str);
	return (ret);
}

static int	create_image(t_texture **tex, const unsigned char *map)
{
	int	i;
	int	j;
	int	y;

	(*tex)->pixels = ft_calloc((*tex)->height, \
		sizeof (*(*tex)->pixels));
	if (!(*tex)->pixels)
		return (ERROR);
	j = 0;
	i = -1;
	while (++i < (*tex)->height)
	{
		y = 0;
		(*tex)->pixels[i] = ft_calloc((*tex)->width, sizeof(t_color));
		if (!(*tex)->pixels[i])
			return (ERROR);
		while (y < (*tex)->width)
		{
			(*tex)->pixels[i][y++] = (t_color){(double)map[j] / (*tex)->value, \
				(double)map[j + 1] / (*tex)->value, \
				(double)map[j + 2] / (*tex)->value};
			j += 3;
		}
	}
	return (SUCCESS);
}

int	read_ppm(t_texture **texture, int fd)
{
	long			bytes;
	unsigned char	*map;

	if (init_texture(fd, texture))
		return (ERROR);
	map = ft_calloc((*texture)->width * (*texture)->height * 3, sizeof (*map));
	if (!map)
		return (print_error(ERROR, "PPM file allocation failed"));
	bytes = read(fd, map, (*texture)->width * (*texture)->height * 3);
	close(fd);
	if (bytes < 0 || bytes != (*texture)->width * (*texture)->height * 3)
		return (print_error(ERROR, "Invalid ppm file"));
	if (create_image(texture, map))
		return (print_error(ERROR, "PPM image allocation failed"));
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
			ret = ft_strtrim(item, "\n \t");
			if (i > 0)
				item[i] = ' ';
			return (ret);
		}
	}
	ret = ft_strtrim(item, "\n \t");
	return (ret);
}

char	*get_header(int fd)
{
	char	*ret;
	char	tmp[2];
	int		nb;

	ret = ft_calloc(2, sizeof (char));
	if (!ret)
		return (NULL);
	tmp[1] = 0;
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
		if (!ret)
			return (NULL);
		if (*tmp == '\n')
			nb++;
	}
	return (ret);
}
