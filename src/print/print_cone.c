/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_cone.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 17:04:57 by ncotte            #+#    #+#             */
/*   Updated: 2023/02/13 23:22:57 by shalimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

unsigned int	print_cone(t_scene *scene, void *object, \
					t_point hit_point, t_point hit_point_to_light)
{
	t_cone	*cone;
	t_color	base;
	t_point	rebound;
	t_point	normal;

	cone = (t_cone *)object;
	normal = add_vectors(get_projection_unit(sub_vectors(hit_point, \
		cone->coord), cone->direction), cone->coord);
	normal = unit_vector(sub_vectors(hit_point, normal));
	if (distance_square(hit_point, cone->center_base) == cone->radius_2)
			normal = scalar_multi(-1.0, cone->direction);
	rebound = reflection(sub_vectors(hit_point, scene->light->coord), normal);
	base = cone->color;
	if (dot_product(normal, unit_vector(sub_vectors(scene->light->coord, \
		hit_point))) <= 0.0)
		return (phong_ambient(scene->amb_light, base));
	return (phong_color(scene, base, dot_product(normal, hit_point_to_light)));
}

t_color	get_color_cone(t_scene *scene, void *object)
{
	t_cone	*cone;

	(void)scene;
	cone = (t_cone *)object;
	return (cone->color);
}

t_point	normal_cone(t_point ray, t_point hit_point, void *object)
{
	t_cone	*cone;
	t_point	normal;

	cone = (t_cone *)object;
	normal = unit_vector(sub_vectors(hit_point, \
		add_vectors(get_projection_unit(sub_vectors(hit_point, \
		cone->coord), cone->direction), cone->coord)));
	if (distance_square(hit_point, cone->center_base) == cone->radius_2)
		normal = scalar_multi(-1.0, cone->direction);
	if (dot_product(normal, ray) <= 0.0)
		return (normal);
	return (scalar_multi(-1.0, normal));
}
