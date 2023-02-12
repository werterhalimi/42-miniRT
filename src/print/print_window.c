/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_window.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 14:39:19 by ncotte            #+#    #+#             */
/*   Updated: 2023/02/09 19:06:31 by shalimi          ###   ########.fr       */
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
			((scene->objects)[i])->object);
		if (!isinf(tmp) && tmp < first_intersect)
		{
			first_intersect = tmp;
			*index = i + 1;
		}
	}
	return (first_intersect);
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
	color = obj->get_color(scene, obj->object);
    if (obj && obj->type == SPHERE)
    {
        t_sphere *sphere = ((t_sphere *)obj->object);
        t_point center = sphere->coord;
        t_point origin = scene->camera->coord;
        t_point hit_point = add_vectors(origin, scalar_multi(first_intersect, ray));
        t_point normal = unit_vector(sub_vectors(hit_point, center));
        double dot = dot_product(ray, normal);
        t_point rebound = unit_vector(sub_vectors(ray, scalar_multi(2.0 * dot, normal)));
        t_point hit_point_to_light = unit_vector(sub_vectors(scene->light->coord, hit_point));
        double dot2 = dot_product(hit_point_to_light, rebound);
        double angle2 = acos(dot2);
        t_color base = sphere->color;

        base.r *= (-M_1_PI) * angle2 + 1;
        base.g *= (-M_1_PI) * angle2 + 1;
        base.b *= (-M_1_PI) * angle2 + 1;

        if (base.r > 255) base.r = 255;
        if (base.r < 0) base.r = 0;
        if (base.g > 255) base.g = 255;
        if (base.g < 0) base.g = 0;
        if (base.b > 255) base.b = 255;
        if (base.b < 0) base.b = 0;
        return color_trgb(base);
    }

	 if (obj && obj->type == PLANE)
    {
        t_plane *plane = ((t_plane *)obj->object);
        t_point origin = scene->camera->coord;
        t_point hit_point = add_vectors(origin, scalar_multi(first_intersect, ray));
		t_point normal = plane->normal;
        double dot = dot_product(ray, normal);
        t_point rebound = unit_vector(sub_vectors(ray, scalar_multi(2.0 * dot, normal)));
        t_point hit_point_to_light = unit_vector(sub_vectors(scene->light->coord, hit_point));
        double dot2 = dot_product(hit_point_to_light, rebound);
        double angle2 = acos(dot2);
        t_color base = plane->color;

        base.r *= (-M_1_PI) * angle2 + 1;
        base.g *= (-M_1_PI) * angle2 + 1;
        base.b *= (-M_1_PI) * angle2 + 1;

        if (base.r > 255) base.r = 255;
        if (base.r < 0) base.r = 0;
        if (base.g > 255) base.g = 255;
        if (base.g < 0) base.g = 0;
        if (base.b > 255) base.b = 255;
        if (base.b < 0) base.b = 0;
        return color_trgb(base);
    }



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
