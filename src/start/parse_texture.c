/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 15:42:50 by shalimi           #+#    #+#             */
/*   Updated: 2023/02/24 19:12:54 by shalimi          ###   ########.fr       */
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

static char	*get_header(int fd)
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

int	init_texture(int fd, t_texture **texture)
{
	char	*tmp;
	char	*line;
	char	**split;

	(*texture) = ft_calloc(1, sizeof (t_texture));
	(*texture)->value = 0;
	(*texture)->height = 0;
	(*texture)->width = 0;
	line = get_header(fd);
	split = ft_split(line, '\n');
	if (ft_strncmp(split[0], "P6", 2))
		return (print_error(ERROR, "PPM file isn't P6"));
	tmp = split[1];
	(*texture)->width = ft_atoi(split[1]);
	while (*(split[1]) && *(split[1]) != ' ')
		(split[1])++;
	(*texture)->height = ft_atoi(split[1]);
	(*texture)->value = ft_atoi(split[2]);
	ft_free(line);
	ft_free(split[0]);
	ft_free(tmp);
	ft_free(split[2]);
	return (SUCCESS);
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

int	parse_texture(void *ptr, char *item)
{
	t_texture	*texture;
	char		*tmp;
	int			fd;

	if (!item)
		return (print_error(ERROR, "A texture is missing"));
	tmp = remove_space(item);
	fd = open(tmp, O_RDONLY);
	ft_free(tmp);
	if (fd < 0)
		return (print_error(ERROR, "Invalid texture file"));
	if (read_ppm(&texture, fd))
		return (ERROR);
	*(t_texture **)ptr = texture;
	return (SUCCESS);
}

t_color	sub_colors(t_color a, t_color b)
{
	return ((t_color){a.r - b.r, a.g - b.g, a.b - b.b});
}

t_color	add_colors(t_color a, t_color b)
{
	return ((t_color){a.r + b.r, a.g + b.g, a.b + b.b});
}

static t_texture	*create_empty_texture(int height, int width, int value)
{
	t_texture	*ret;
	int			y;

	ret = ft_calloc(sizeof(*ret), 1);
	ret->height = height;
	ret->width = width;
	ret->value = value;
	ret->pixels = ft_calloc(ret->height, sizeof (*ret->pixels));
	y = 0;
	while (y < ret->height)
	{
		ret->pixels[y] = ft_calloc(ret->width, sizeof(t_color));
		y++;
	}
	return (ret);
}

static t_texture	*bump_to_map(t_texture *bump)
{
	t_texture	*ret;
	int			x;
	int			y;

	ret = create_empty_texture(bump->height, bump->width, bump->value);
	y = -1;
	while (++y < ret->height)
	{
		x = -1;
		while (++x < ret->width)
		{
				ret->pixels[y][x] = sub_colors(bump->pixels[y][x], \
						bump->pixels[y][x + 1]);
				ret->pixels[y][x] = add_colors(\
						ret->pixels[y][x], \
						sub_colors(bump->pixels[y][x], bump->pixels[y + 1][x]));
		}
	}
	y = -1;
	while (++y < bump->height)
		ft_free(bump->pixels[y]);
	ft_free(bump->pixels);
	ft_free(bump);
	return (ret);
}

int	parse_normal_map(void *ptr, char *item)
{
	t_texture	*normal_map;
	char		*tmp;
	int			fd;

	if (!item)
		return (print_error(ERROR, "A texture is missing"));
	tmp = ft_strtrim(item, "\n \t");
	fd = open(tmp, O_RDONLY);
	ft_free(tmp);
	if (fd < 0)
		return (print_error(ERROR, "Invalid texture file"));
	if (read_ppm(&normal_map, fd))
		return (ERROR);
	*(t_texture **)ptr = bump_to_map(normal_map);
	return (SUCCESS);
}
