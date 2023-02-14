/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 14:36:28 by ncotte            #+#    #+#             */
/*   Updated: 2023/02/13 22:57:28 by shalimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

unsigned int	print_cylinder(t_scene *scene, void *object, \
					t_point hit_point, t_point hit_point_to_light)
{
	t_cylinder	*cy;
	t_color		base;
	t_point		rebound;
	t_point		normal;

	cy = (t_cylinder *)object;
	normal = add_vectors(get_projection_unit(sub_vectors(hit_point, \
		cy->coord), cy->direction), cy->coord);
	normal = unit_vector(sub_vectors(hit_point, normal));
	if (distance_square(hit_point, cy->center_top) <= cy->radius_2)
			normal = cy->direction;
	if (distance_square(hit_point, cy->center_down) <= cy->radius_2)
			normal = scalar_multi(-1.0, cy->direction);
	rebound = reflection(sub_vectors(hit_point, scene->light->coord), normal);
	base = cy->color;
	if (dot_product(normal, unit_vector(sub_vectors(scene->light->coord, \
		hit_point))) <= 0.0)
		return (phong_ambient(scene->amb_light, base));
	return (phong_color(scene, base, dot_product(normal, hit_point_to_light)));
}

t_color	get_color_cylinder(t_scene *scene, void *object)
{
	t_cylinder	*cylinder;

	(void)scene;
	cylinder = (t_cylinder *)object;
	return (cylinder->color);
}

t_point	normal_cylinder(t_point ray, t_point hit_point, void *object)
{
	t_cylinder	*cylinder;
	t_point		normal;

	cylinder = (t_cylinder *)object;
	normal = unit_vector(sub_vectors(hit_point, \
		add_vectors(get_projection_unit(sub_vectors(hit_point, \
		cylinder->coord), cylinder->direction), cylinder->coord)));
	if (distance_square(hit_point, cylinder->center_top) <= cylinder->radius_2)
		normal = cylinder->direction;
	if (distance_square(hit_point, cylinder->center_down) <= cylinder->radius_2)
		normal = scalar_multi(-1.0, cylinder->direction);
	if (dot_product(normal, ray) <= 0.0)
		return (normal);
	return (scalar_multi(-1.0, normal));
}
