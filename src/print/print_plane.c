/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_plane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 14:36:36 by ncotte            #+#    #+#             */
/*   Updated: 2023/02/13 22:39:45 by shalimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

unsigned int	print_plane(t_scene *scene, t_plane *plane \
		, t_point hit_point, t_point hit_point_to_light)
{
	t_color	base;
	double	angle2;
	t_point	rebound;
	t_point	normal;

	normal = plane->normal;
	rebound = reflection(sub_vectors(hit_point, scene->light->coord), normal);
	angle2 = vector_angle(normal, unit_vector(sub_vectors(scene->light->coord, hit_point)));
	base= plane->color;
	if (angle2 >= M_PI_2)
		return create_trgb(0,
				(scene->amb_light->color.r + base.r) / 255 * scene->amb_light->ratio,
				(scene->amb_light->color.g + base.g) / 255 * scene->amb_light->ratio,
				(scene->amb_light->color.b + base.b) / 255 * scene->amb_light->ratio
				);

	return phong_color(scene, base, dot_product(normal, hit_point_to_light));

}

double	intersect_plane(t_point ray, void *object, t_point *origin)
{
	t_plane	*plane;
	double	value;
	double	div;
	double	t;

	plane = (t_plane *)object;
	div = dot_product(ray, plane->normal);
	if (!div)
		return (INFINITY);
	value = plane->value;
	if (origin)
		value = dot_product(sub_vectors(plane->coord, *origin), plane->normal);
	t = value / div;
	if (t < 0.0)
		return (INFINITY);
	return (t);
}
