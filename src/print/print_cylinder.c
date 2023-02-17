/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 14:36:28 by ncotte            #+#    #+#             */
/*   Updated: 2023/02/16 03:47:44 by shalimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	print_cylinder(t_phong *phong)
{
	if (dot_product(phong->normal, unit_vector(sub_vectors(phong->coord, \
		phong->hit_point))) <= 0.0)
		return ;
	(phong_diffuse(phong, dot_product(phong->normal, phong->light_ray)));
}

t_color	get_color_cylinder(t_scene *scene, void *object, \
			t_point hit_point, t_point normal)
{
	t_cylinder	*cylinder;
	t_point		vector;
	double		h;
	long		a;

	(void) scene;
	(void) normal;
	cylinder = (t_cylinder *)object;
	if (!cylinder->color_bis)
		return (cylinder->color);
	vector = sub_vectors(hit_point, cylinder->coord);
	a = (long)floor(atan(dot_product(vector, cylinder->right) \
		/ dot_product(vector, cylinder->down)) * 8 * M_1_PI);
	h = dot_product(vector, cylinder->direction);
	if (-(cylinder->semi_height - FLT_EPSILON) < h \
		&& h < cylinder->semi_height - FLT_EPSILON)
	{
		if (!((long)floor(h) % 2) ^ !(a % 2))
			return (*cylinder->color_bis);
		return (cylinder->color);
	}
	if (!((long)floor(sqrt(norm_square(sub_vectors(vector, \
		scalar_multi(h, cylinder->direction))))) % 2) ^ !(a % 2))
		return (*cylinder->color_bis);
	return (cylinder->color);
}

t_point	normal_cylinder(t_point ray, t_point hit_point, void *object)
{
	t_cylinder	*cylinder;
	t_point		normal;
	t_point		projection;

	cylinder = (t_cylinder *)object;
	projection = get_projection_unit(sub_vectors(hit_point, \
		cylinder->coord), cylinder->direction);
	if (norm_square(projection) >= cylinder->semi_height_2 - FLT_EPSILON)
	{
		if ((dot_product(projection, cylinder->direction) <= 0.0) \
			!= (dot_product(projection, ray) >= 0.0))
			return (scalar_multi(-1.0, cylinder->direction));
		return (cylinder->direction);
	}
	normal = unit_vector(sub_vectors(hit_point, \
		add_vectors(projection, cylinder->coord)));
	if (dot_product(normal, ray) > 0.0)
		normal = scalar_multi(-1.0, normal);
	return (normal);
}
