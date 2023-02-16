/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 14:36:28 by ncotte            #+#    #+#             */
/*   Updated: 2023/02/16 02:20:03 by shalimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	print_cylinder(t_phong *phong)
{
	t_cylinder	*cy;

	cy = (t_cylinder *)phong->object;
	if (dot_product(phong->normal, unit_vector(sub_vectors(phong->coord, \
		phong->hit_point))) <= 0.0)
		return ;
	(phong_diffuse(phong, dot_product(phong->normal, phong->light_ray)));
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
