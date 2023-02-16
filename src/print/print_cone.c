/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_cone.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 17:04:57 by ncotte            #+#    #+#             */
/*   Updated: 2023/02/16 17:18:41 by shalimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	print_cone(t_phong *phong)
{
	if (dot_product(phong->normal, unit_vector(sub_vectors(phong->coord, \
		phong->hit_point))) <= 0.0)
		return ;
	(phong_diffuse(phong, dot_product(phong->normal, phong->light_ray)));
}

t_color	get_color_cone(t_scene *scene, void *object, \
			t_point hit_point, t_point normal)
{
	t_cone	*cone;

	(void) scene;
	(void) hit_point;
	(void) normal;
	cone = (t_cone *)object;
	if (!cone->color_bis)
		return (cone->color);
	return (cone->color);
}

t_point	normal_cone(t_point ray, t_point hit_point, void *object)
{
	t_cone	*cone;
	t_point	normal;
	t_point	pro;;

	cone = (t_cone *)object;
	pro = add_vectors(get_projection_unit(sub_vectors(hit_point, \
		cone->coord), cone->direction), cone->coord);
	normal = unit_vector(sub_vectors(hit_point, \
		pro));
	if (distance_square(cone->coord, hit_point) >= cone->height_2)
		normal =  cone->direction;
	if (dot_product(normal, ray) <= 0.0)
		return (normal);
	return (scalar_multi(-1.0, normal));
}
