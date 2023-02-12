/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_window.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 14:39:19 by ncotte            #+#    #+#             */
/*   Updated: 2023/02/12 19:06:10 by shalimi          ###   ########.fr       */
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
	t_point origin = scene->camera->coord;
	t_point hit_point = add_vectors(origin, scalar_multi(first_intersect, ray));
    if (obj && obj->type == SPHERE)
    {
        t_sphere *sphere = ((t_sphere *)obj->object);
        t_point center = sphere->coord;
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

        return color_trgb(base);
    }

	 if (obj && obj->type == PLANE)
    {
        t_plane *plane = ((t_plane *)obj->object);
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

        return color_trgb(base);
    }

	 if(obj && obj->type == CYLINDER)
	 {
		 t_cylinder	*cy = (t_cylinder *) obj->object;
		 t_point	hit_vector = sub_vectors(hit_point, cy->coord);
		 t_point	pro = add_vectors(get_projection(hit_vector, cy->direction), cy->coord);
		 t_point	normal = sub_vectors(hit_point, pro);
		if (distance_square(hit_point, cy->center_top) <= cy->radius_square)
			normal = cy->direction;
 		if (distance_square(hit_point, cy->center_down) <= cy->radius_square)
			normal = scalar_multi(-1.0, cy->direction);
		double dot = dot_product(ray, normal);
        t_point rebound = unit_vector(sub_vectors(ray, scalar_multi(2.0 * dot, normal)));
        t_point hit_point_to_light = unit_vector(sub_vectors(scene->light->coord, hit_point));
        double dot2 = dot_product(hit_point_to_light, rebound);
        double angle2 = acos(dot2);
        t_color base = cy->color;

        base.r *= (-M_1_PI) * angle2 + 1;
        base.g *= (-M_1_PI) * angle2 + 1;
        base.b *= (-M_1_PI) * angle2 + 1;

        return color_trgb(base);

	 }



	return (color);
}

int	print_window(t_scene *scene)
{
	int		x;
	int		y;
	t_point	tmp;
	t_point	ray;
	t_point	unit;

	x = -1;
	tmp = scene->window_corner;
	while (++x < scene->width)
	{
		y = -1;
		ray = tmp;
		while (++y < scene->height)
		{
			unit = unit_vector(ray);
			put_pixel(scene, x, y, find_color_pixel(scene, unit));
			ray = add_vectors(ray, scene->camera->shift_y);
		}
		tmp = add_vectors(tmp, scene->camera->shift_x);
	}
	mlx_put_image_to_window(scene->mlx, scene->window, scene->image, 0, 0);
	return (SUCCESS);
}
