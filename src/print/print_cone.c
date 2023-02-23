/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_cone.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 17:04:57 by ncotte            #+#    #+#             */
/*   Updated: 2023/02/22 01:05:13 by shalimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_color	get_color_cone(t_scene *scene, t_object *object, \
			t_point hit_point, t_point normal)
{
	t_cone	*cone;
	t_point	vector;
	double	h;
	long	a;

	(void) scene;
	(void) normal;
	cone = (t_cone *)object->object;
	if (!object->color_bis)
		return (cone->ratio_color);
	vector = sub_vectors(hit_point, cone->coord);
	a = (long)floor(atan(dot_product(vector, cone->right) \
		/ dot_product(vector, cone->down)) * MC_8_PI);
	h = dot_product(vector, cone->direction);
	if (h < cone->height - FLT_EPSILON)
	{
		if (!((long)floor(h) % 2) ^ !(a % 2))
			return (*object->color_bis);
		return (cone->ratio_color);
	}
	if (!((long)floor(sqrt(distance_square(vector, \
		scalar_multi(h, cone->direction)))) % 2) ^ !(a % 2))
		return (*object->color_bis);
	return (cone->ratio_color);
}

t_point	normal_cone(t_point ray, t_point hit_point, \
			void *object, t_texture *texture)
{
	t_cone	*cone;
	t_point	normal;
	t_point	chp;
	t_point	y;
	double	t;

	(void) texture;
	cone = (t_cone *)object;
	chp = (sub_vectors(hit_point, cone->coord));
	t = norm_square(chp) / dot_product(chp, cone->direction);
	y = add_vectors(cone->coord, scalar_multi(t, cone->direction));
	normal = unit_dist(hit_point, y);
	if (dot_product(unit_dist(hit_point, cone->center_base), \
		cone->direction) >= -0.01)
		normal = cone->direction;
	if (dot_product(normal, ray) <= 0.0)
		return (normal);
	return (scalar_multi(-1.0, normal));
}
