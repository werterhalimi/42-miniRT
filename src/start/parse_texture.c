/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 15:42:50 by shalimi           #+#    #+#             */
/*   Updated: 2023/02/25 19:32:06 by shalimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

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

int	parse_normal_map(void *ptr, char *item)
{
	t_texture	*normal_map;
	char		*tmp;
	int			fd;

	if (!item)
		return (print_error(ERROR, "A texture is missing"));
	tmp = remove_space(item);
	fd = open(tmp, O_RDONLY);
	ft_free(tmp);
	if (fd < 0)
		return (print_error(ERROR, "Invalid texture file"));
	if (read_ppm(&normal_map, fd))
		return (ERROR);
	*(t_texture **)ptr = normal_map;
	return (SUCCESS);
}

int	parse_bump_map(void *ptr, char *item)
{
	t_texture	*normal_map;
	char		*tmp;
	int			fd;

	if (!item)
		return (print_error(ERROR, "A texture is missing"));
	tmp = remove_space(item);
	fd = open(tmp, O_RDONLY);
	ft_free(tmp);
	if (fd < 0)
		return (print_error(ERROR, "Invalid texture file"));
	if (read_ppm(&normal_map, fd))
		return (ERROR);
	*(t_texture **)ptr = bump_to_map(normal_map);
	if (!ptr)
		return (print_error(ERROR, "Bump map to normal map failed"));
	return (SUCCESS);
}
