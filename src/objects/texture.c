/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 19:16:38 by shalimi           #+#    #+#             */
/*   Updated: 2023/02/24 19:29:26 by shalimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

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

t_texture	*bump_to_map(t_texture *bump)
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
