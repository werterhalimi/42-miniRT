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

unsigned int	print_plane(t_scene *scene, void *object, \
					t_point hit_point, t_point hit_point_to_light)
{
	t_plane	*plane;
	t_color	base;
	t_point	rebound;
	t_point	normal;

	plane = (t_plane *)object;
	normal = plane->normal;
	rebound = reflection(sub_vectors(hit_point, scene->light->coord), normal);
	base = plane->color;
	if (dot_product(normal, unit_vector(sub_vectors(scene->light->coord, \
		hit_point))) <= 0.0)
		return (phong_ambient(scene->amb_light, base));
	return (phong_color(scene, base, dot_product(normal, hit_point_to_light)));
}

t_color	get_color_plane(t_scene *scene, void *object)
{
	t_plane	*plane;

	(void)scene;
	plane = (t_plane *)object;
	return (plane->color);
}

t_point	normal_plane(t_point ray, t_point hit_point, void *object)
{
	t_plane	*plane;

	(void) hit_point;
	plane = (t_plane *)object;
	if (dot_product(plane->normal, ray) <= 0.0)
		return (plane->normal);
	return (scalar_multi(-1.0, plane->normal));
}
