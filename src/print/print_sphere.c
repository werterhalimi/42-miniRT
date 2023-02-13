/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 14:36:43 by ncotte            #+#    #+#             */
/*   Updated: 2023/02/13 22:34:40 by shalimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

unsigned int	print_sphere(t_scene *scene, t_sphere *sphere \
		, t_point hit_point, t_point hit_point_to_light)
{
	t_color	base;
	double	angle2;
	t_point	rebound;
	t_point	normal;

	normal = unit_vector(sub_vectors(hit_point, sphere->coord));
	rebound = reflection(sub_vectors(hit_point, scene->light->coord), normal);
	angle2 = vector_angle(normal, unit_vector(sub_vectors(scene->light->coord, hit_point)));
	base= sphere->color;


//t_point h = unit_vector(add_vectors(scalar_multi(-1.0, ray), hit_point_to_light));
	//double specular = pow(dot_product(normal, h), 25);

	if (angle2 >= M_PI_2)
		return create_trgb(0,
				(scene->amb_light->color.r + base.r) / 255 * scene->amb_light->ratio,
				(scene->amb_light->color.g + base.g) / 255 * scene->amb_light->ratio,
				(scene->amb_light->color.b + base.b) / 255 * scene->amb_light->ratio
				);

	return phong_color(scene, base, dot_product(normal, hit_point_to_light));
/*	return create_trgb(0,
			(scene->amb_light->color.r + base.r) / 255 * scene->amb_light->ratio + (scene->light->color.r * base.r * dot_product(normal, hit_point_to_light) / 255) *scene->light->ratio, //+  specular * (scene->light->color.r - base.r),
			(scene->amb_light->color.g + base.g) / 255 * scene->amb_light->ratio + (scene->light->color.g * base.g * dot_product(normal, hit_point_to_light) / 255) *scene->light->ratio, //+  specular * (scene->light->color.g - base.g),
			(scene->amb_light->color.b + base.b) / 255 * scene->amb_light->ratio + (scene->light->color.b * base.b * dot_product(normal, hit_point_to_light) / 255) *scene->light->ratio //+  specular * (scene->light->color.b - base.b)
			);*/
}

double	intersect_sphere(t_point ray, void *object, t_point *origin)
{
	t_sphere	*sphere;
	t_point		oc;
	double		value;
	double		t1;
	double		t2;

	sphere = (t_sphere *)object;
	oc = sphere->relative_coord;
	value = sphere->value;
	if (origin)
	{
		oc = sub_vectors(*origin, sphere->coord);
		value = norm_square(oc) - sphere->radius_2;
	}
	t1 = quad_solv(1.0, 2.0 * dot_product(ray, oc), value, &t2);
	if (!isnan(t1) && t1 < t2 && t1 >= 0.0)
		return (t1);
	if (!isnan(t2) && t2 >= 0.0)
		return (t2);
	return (INFINITY);
}
