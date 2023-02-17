/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 14:36:43 by ncotte            #+#    #+#             */
/*   Updated: 2023/02/17 21:04:02 by shalimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"



t_color	get_color_sphere(t_scene *scene, void *object, \
			t_point hit_point, t_point normal)
{
	t_sphere	*sphere;
	t_point		vector;
	long		a;
	long		b;

	(void) scene;
	(void) normal;
	sphere = (t_sphere *)object;
	if (!sphere->color_bis)
		return (sphere->color);
	vector = sub_vectors(hit_point, sphere->coord);
	a = (long)floor(atan(dot_product(vector, sphere->right) \
		/ dot_product(vector, sphere->down)) * 8 * M_1_PI);
	b = (long)floor(asin(dot_product(vector, sphere->front) \
		/ sphere->radius) * 8 * M_1_PI);
	if (!(a % 2) ^ !(b % 2))
		return (*sphere->color_bis);
	return (sphere->color);
}

t_point	normal_sphere(t_point ray, t_point hit_point, void *object)
{
	t_sphere	*sphere;
	t_point		normal;

	sphere = (t_sphere *)object;
	normal = unit_vector(sub_vectors(hit_point, sphere->coord));
	if (dot_product(normal, ray) <= 0.0)
		return (normal);
	return (scalar_multi(-1.0, normal));
}
