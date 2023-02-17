/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_cone.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 17:04:57 by ncotte            #+#    #+#             */
/*   Updated: 2023/02/17 03:14:57 by shalimi          ###   ########.fr       */
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
	t_point	chp;
	t_point	y;
//	t_point tmp;
	double	t;

	cone = (t_cone *)object;
	chp = (sub_vectors(hit_point, cone->coord));
	t = norm_square(chp) / dot_product(chp,cone->direction);
	y = add_vectors(cone->coord, scalar_multi(t, cone->direction));
	normal = unit_vector(sub_vectors(hit_point, y));
	if (dot_product(cone->direction, unit_vector(sub_vectors(hit_point, \
		cone->center_base))) >= -0.01)
		normal = cone->direction;
//	(void) ray;
//	return (normal);

//	tmp = sub_vectors(hit_point, cone->coord);
//	t = dot_product(tmp, cone->direction);
//	normal = cone->direction;
//	if (t < cone->height - FLT_EPSILON)
//	{
//		normal = scalar_multi(t, normal);
//		tmp = add_vectors(normal, cone->coord);
//		t = norm_square(sub_vectors(hit_point, \
//			tmp)) * inv_sqrt(norm_square(normal));
//		normal = scalar_multi(t, cone->direction);
//		tmp = sub_vectors(hit_point,add_vectors(normal, tmp));
//		normal = unit_vector(tmp);
//
////		normal = cross_product(tmp, cone->direction);
////		normal = cross_product(tmp, normal);
//	}
	if (dot_product(normal, ray) <= 0.0)
		return (normal);
	return (scalar_multi(-1.0, normal));
}
