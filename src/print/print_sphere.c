/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 14:36:43 by ncotte            #+#    #+#             */
/*   Updated: 2023/02/21 18:58:09 by shalimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static t_color	sphere_map(t_texture *tex, double a, double b)
{
	double	tu;
	double	tv;

	tu = 1 - (b * M_1_PI + 0.5);
	tv = (a/(2 * M_PI) + 0.25);

	return (tex->pixels[(int)(tu * tex->height)][(int)(tv * tex->width)]);
}

t_color	get_color_sphere(t_scene *scene, t_object *object, \
			t_point hit_point, t_point normal)
{
	t_sphere	*sphere;
	t_point		vector;
	double		a;
	double		b;
	double		c;

	(void) scene;
	(void) normal;
	sphere = (t_sphere *)object->object;
	if (!object->color_bis && !object->texture)
		return (sphere->color);
	vector = sub_vectors(hit_point, sphere->coord);
	c = acos(dot_product(vector, sphere->right) * inv_sqrt(pow(dot_product(vector, sphere->right), 2) + pow(dot_product(vector, sphere->down),2)));
	if (dot_product(vector, sphere->down) < 0)
		c *= -1.0;

	// -pi/2 -- pi / 2
	a = (atan(dot_product(vector, sphere->down) \
		/ dot_product(vector, sphere->right)));
	if (dot_product(vector, sphere->right) < 0)
		a += M_PI;
	// - pi / 2 -- pi/2
	b = (asin(dot_product(vector, sphere->front) \
		/ sphere->radius));
	if (object->texture)
		return (sphere_map(object->texture, a, b));

	if (!((long)floor(a * 8 * M_1_PI) % 2) ^ !((long)floor(b * 8 * M_1_PI) % 2))
		return (*object->color_bis);
	return (sphere->color);
}

t_point	normal_sphere(t_point ray, t_point hit_point, void *object)
{
	t_sphere	*sphere;
	t_point		normal;

	sphere = (t_sphere *)object;
	normal = unit_dist(hit_point, sphere->coord);

	if (dot_product(normal, ray) <= 0.0)
		return (normal);
	return (scalar_multi(-1.0, normal));
}
