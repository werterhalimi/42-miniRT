/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_graduation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 10:15:53 by ncotte            #+#    #+#             */
/*   Updated: 2023/02/24 10:15:57 by ncotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static int	is_valid_coord(t_base *base, t_axis *axis, int u, int v)
{
	int	value;

	if (isinf(axis->slope))
		return (((base->half_height <= v && v <= axis->proj_v) \
			|| (axis->proj_v <= v && v <= base->half_height)) \
			&& u == base->half_width);
	value = (int)round(axis->slope * u + axis->origin);
	return (((base->half_width <= u && u <= axis->proj_u) \
		|| (axis->proj_u <= u && u <= base->half_width)) \
		&& ((base->half_height <= v && v <= axis->proj_v) \
		|| (axis->proj_v <= v && v <= base->half_height)) \
		&& (value - axis->epsilon <= v && v <= value + axis->epsilon));
}

static void	print_axis(t_image *image, t_base *base, int u, int v)
{
	if (is_valid_coord(base, &base->x_axis, u, v))
		put_pixel(image, u, v, create_trgb(0, 255, 0, 0));
	else if (is_valid_coord(base, &base->y_axis, u, v))
		put_pixel(image, u, v, create_trgb(0, 0, 255, 0));
	else if (is_valid_coord(base, &base->z_axis, u, v))
		put_pixel(image, u, v, create_trgb(0, 0, 0, 255));
	else
		put_pixel(image, u, v, create_trgb(128, 255, 255, 255));
}

static t_axis	init_axis(t_base *base, t_point vector)
{
	t_axis	axis;

	axis.vector = matrix_vector_multi(base->matrix, vector);
	axis.delta_u = axis.vector.x * base->half_width;
	axis.delta_v = axis.vector.y * base->half_height;
	axis.proj_u = (int)round(axis.delta_u) + base->half_width;
	axis.proj_v = (int)round(axis.delta_v) + base->half_height;
	axis.slope = axis.delta_v / axis.delta_u;
	if (!isinf(axis.slope))
	{
		axis.origin = base->half_height - axis.slope * base->half_width;
		axis.epsilon = abs((int)ceil(axis.slope) >> 1);
	}
	return (axis);
}

void	print_graduation(t_scene *scene)
{
	t_base	base;
	int		u;
	int		v;

	base.half_width = scene->axis_img->width >> 1;
	base.half_height = scene->axis_img->height >> 1;
	base.matrix = new_matrix(scene->camera->right, \
		scene->camera->down, scene->camera->front);
	base.x_axis = init_axis(&base, new_point(1.0, 0.0, 0.0));
	base.y_axis = init_axis(&base, new_point(0.0, 1.0, 0.0));
	base.z_axis = init_axis(&base, new_point(0.0, 0.0, 1.0));
	u = -1;
	while (++u < scene->axis_img->width)
	{
		v = -1;
		while (++v < scene->axis_img->height)
			print_axis(scene->axis_img, &base, u, v);
	}
	mlx_put_image_to_window(scene->mlx, scene->window, \
		scene->axis_img->ptr, 0, 0);
}
