/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_window.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 14:39:19 by ncotte            #+#    #+#             */
/*   Updated: 2023/02/13 23:15:16 by shalimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

double	find_intersect(t_scene *scene, t_point ray, int *index)
{
	double			first_intersect;
	double			tmp;
	int				i;

	i = -1;
	*index = 0;
	first_intersect = INFINITY;
	while ((scene->objects)[++i])
	{
		tmp = ((scene->objects)[i])->intersect(ray, \
			((scene->objects)[i])->object, NULL);
		if (!isinf(tmp) && tmp < first_intersect)
		{
			first_intersect = tmp;
			*index = i + 1;
		}
	}
	return (first_intersect);
}

int	find_intersect_light(t_scene *scene, t_point ray, t_point origin, t_objects *sender)
{
	double			first_intersect;
	double			tmp;
	int				i;
	t_objects		*obj;

	i = 0;
	obj = sender;
	first_intersect = INFINITY;
	while ((scene->objects)[++i])
	{
		tmp = ((scene->objects)[i])->intersect(ray, \
			((scene->objects)[i])->object, &origin);
		if (!isinf(tmp) && tmp < first_intersect && scene->objects[i] != sender)
		{
			first_intersect = tmp;
			obj = scene->objects[i];
		}
	}
	return (obj != sender);
}



static unsigned int	find_color_pixel(t_scene *scene, t_point ray)
{
	unsigned int	color;
	double			first_intersect;
	t_objects       *obj;
	int				i;

	first_intersect = find_intersect(scene, ray, &i);
	if (!i--)
		return (0);
	obj = (scene->objects)[i];
	t_point origin = scene->camera->coord;
	t_point hit_point = add_vectors(origin, scalar_multi(first_intersect, ray));
	t_point hit_point_to_light = unit_vector(sub_vectors(scene->light->coord, hit_point));
	color = obj->get_color(scene, obj->object);
	if (find_intersect_light(scene, hit_point_to_light, hit_point, obj))
	{
		return create_trgb(0,
				(scene->amb_light->color.r + color_get_r(color)) / 255 * scene->amb_light->ratio,
				(scene->amb_light->color.g + color_get_g(color)) / 255 * scene->amb_light->ratio,
				(scene->amb_light->color.b + color_get_b(color)) / 255 * scene->amb_light->ratio);

	}
	if (obj && obj->type == SPHERE)
		return 	print_sphere(scene, (t_sphere *) obj->object, hit_point, hit_point_to_light);
	if (obj && obj->type == PLANE)
		return 	print_plane(scene, (t_plane *) obj->object, hit_point, hit_point_to_light);
	if(obj && obj->type == CYLINDER)
		return 	print_cylinder(scene, (t_cylinder *) obj->object, hit_point, hit_point_to_light);
	if(obj && obj->type == CONE)
		return 	print_cone(scene, (t_cone *) obj->object, hit_point, hit_point_to_light);
	return (color);
}

void	print_window(t_scene *scene, int offset)
{
	int				x;
	int				y;
	t_point			tmp;
	t_point			ray;
	unsigned int	color;

	x = -1;
	tmp = scene->window_corner;
	while (++x < scene->width)
	{
		y = -1;
		ray = tmp;
		while (++y < scene->height)
		{
			if (!(x % offset) && !(y % offset))
				color = find_color_pixel(scene, unit_vector(ray));
			else if (x % offset && !(y % offset))
				color = get_pixel_color(scene, x - x % offset, y);
			put_pixel(scene, x, y, color);
			ray = add_vectors(ray, scene->camera->shift_y);
		}
		color = get_pixel_color(scene, x, 0);
		tmp = add_vectors(tmp, scene->camera->shift_x);
	}
	mlx_put_image_to_window(scene->mlx, scene->window, scene->image, 0, 0);
}
