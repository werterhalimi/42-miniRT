/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_window.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 14:39:19 by ncotte            #+#    #+#             */
/*   Updated: 2023/02/01 14:39:21 by ncotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	update_objects(t_scene *scene)
{
	int	i;

	i = -1;
	while ((scene->objects)[++i])
		(scene->objects)[i]->update(scene, ((scene->objects)[i])->object);
}

static unsigned int	find_color_pixel(t_scene *scene, t_point ray)
{
	unsigned int	color;
	double			first_intersect;
	double			tmp;
	int				i;

	i = -1;
	color = 0;
	first_intersect = INFINITY;
	while ((scene->objects)[++i])
	{
		tmp = ((scene->objects)[i])->intersect(ray, \
			((scene->objects)[i])->object);
		if (!isinf(tmp) && tmp < first_intersect)
		{
			first_intersect = tmp;
			color = ((scene->objects)[i])->get_color(scene, \
				((scene->objects)[i])->object);
		}
	}
	return (color);
}

int	print_window(t_scene *scene)
{
	int		x;
	int		y;
	t_point	tmp;
	t_point	ray;

	x = -1;
	tmp = scene->window_corner;
	update_objects(scene);
	while (++x < scene->width)
	{
		y = -1;
		ray = tmp;
		while (++y < scene->height)
		{
			put_pixel(scene, x, y, find_color_pixel(scene, unit_vector(ray)));
			ray = add_vectors(ray, scene->camera->shift_y);
		}
		tmp = add_vectors(tmp, scene->camera->shift_x);
	}
	mlx_put_image_to_window(scene->mlx, scene->window, scene->image, 0, 0);
	return (SUCCESS);
}
