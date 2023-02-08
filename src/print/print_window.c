/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_window.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 14:39:19 by ncotte            #+#    #+#             */
/*   Updated: 2023/02/08 22:03:42 by shalimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	update_objects(t_scene *scene)
{
	int	i;

	i = -1;
	while ((scene->objects)[++i])
		(scene->objects)[i]->update(scene, (scene->objects)[i]->object);
}

static unsigned int	find_color_pixel(t_scene *scene, t_point ray)
{
	unsigned int	color;
	double			first_intersect;
	double			tmp;
	t_objects		*obj;
	int				i;

	i = -1;
	color = 0;
	obj = 0;
	first_intersect = INFINITY;
	while ((scene->objects)[++i])
	{
		tmp = ((scene->objects)[i])->intersect(ray, \
			((scene->objects)[i])->object);
		if (!isinf(tmp) && tmp < first_intersect)
		{
			first_intersect = tmp;
			obj = (scene->objects)[i];
			color = ((scene->objects)[i])->get_color(scene, \
				((scene->objects)[i])->object);
		}
	}
	if (obj && obj->type == SPHERE)
	{
		t_sphere *sphere = ((t_sphere *)obj->object);
		t_point	center = sphere->coord;
		t_point origin = scene->camera->coord;
		t_point hit_point = add_vectors(origin, scalar_multi(first_intersect, ray));
		t_point	normal = unit_vector(sub_vectors(hit_point, center));
		double dot = dot_product(ray, normal);
		double angle = acos(dot);
		t_point dir = add_vectors(add_vectors(hit_point, ray), scalar_multi(2, normal));
		printf("%f %f\n", dir.x, unit_vector(dir).x);
		t_point rebound = sub_vectors(ray, scalar_multi(2.0 * dot, normal));
		if (rebound.x != unit_vector(rebound).x)
			printf("nop\n");
		return create_trgb(1, 0, 100, angle*55);

	}
	return (color);
}

int	print_window(t_scene *scene)
{
	int		x;
	int		y;
	t_point	tmp;
	t_point	ray;
	t_point unit;

	x = -1;
	tmp = scene->window_corner;
	update_objects(scene);
	while (++x < scene->width)
	{
		y = -1;
		ray = tmp;
		while (++y < scene->height)
		{
			unit = unit_vector(ray);
			if (x == 960 && y == 540)
				printf("Center : (%lf, %lf, %lf)\n", unit.x, unit.y, unit.z);
			put_pixel(scene, x, y, find_color_pixel(scene, unit));
			ray = add_vectors(ray, scene->camera->shift_y);
		}
		tmp = add_vectors(tmp, scene->camera->shift_x);
	}
	mlx_put_image_to_window(scene->mlx, scene->window, scene->image, 0, 0);
	return (SUCCESS);
}
