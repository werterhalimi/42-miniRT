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
	if (!ret)
		return (NULL);
	ret->height = height;
	ret->width = width;
	ret->value = value;
	ret->pixels = ft_calloc(ret->height, sizeof (*ret->pixels));
	if (!ret->pixels)
		return (NULL);
	y = 0;
	while (y < ret->height)
	{
		ret->pixels[y] = ft_calloc(ret->width, sizeof(t_color));
		if (!ret->pixels[y++])
			return (NULL);
	}
	return (ret);
}

t_texture	*bump_to_map(t_texture *bump)
{
	t_texture	*ret;
	int			u;
	int			v;

	ret = create_empty_texture(bump->height, bump->width, bump->value);
	if (!ret)
		return (NULL);
	v = -1;
	while (++v < ret->height)
	{
		u = -1;
		while (++u < ret->width)
		{
				ret->pixels[v][u] = sub_colors(bump->pixels[v][u], \
						bump->pixels[v][u + 1]);
				ret->pixels[v][u] = add_colors(\
						ret->pixels[v][u], \
						sub_colors(bump->pixels[v][u], bump->pixels[v + 1][u]));
		}
	}
	while (--v >= 0)
		ft_free(bump->pixels[v]);
	ft_free(bump->pixels);
	ft_free(bump);
	return (ret);
}

int	init_texture(int fd, t_texture **texture)
{
	char	*line;
	char	**split;

	*texture = ft_calloc(1, sizeof (t_texture));
	if (!(*texture))
		return (print_error(ERROR, "Texture allocation failed"));
	line = get_header(fd);
	if (!line)
		return (print_error(ERROR, "PPM header allocation failed"));
	split = ft_split(line, '\n');
	if (!split)
		return (print_error(ERROR, "Texture init failed because of split"));
	if (ft_strncmp(split[0], "P6", 2))
		return (print_error(ERROR, "PPM file isn't P6"));
	(*texture)->width = ft_atoi(split[1]);
	while (*(split[1]) && *(split[1]) != ' ')
		(split[1])++;
	(*texture)->height = ft_atoi(split[1]);
	(*texture)->value = ft_atoi(split[2]);
	return (SUCCESS);
}
