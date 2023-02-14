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

unsigned int	print_sphere(t_scene *scene, void *object, \
					t_point hit_point, t_point hit_point_to_light)
{
	t_sphere	*sphere;
	t_color		base;
	t_point		rebound;
	t_point		normal;

	sphere = (t_sphere *)object;
	normal = unit_vector(sub_vectors(hit_point, sphere->coord));
	rebound = reflection(sub_vectors(hit_point, scene->light->coord), normal);
	base = sphere->color;
//	t_point h = unit_vector(add_vectors(scalar_multi(-1.0, ray), hit_point_to_light));
//	double specular = pow(dot_product(normal, h), 25);
	if (dot_product(normal, unit_vector(sub_vectors(scene->light->coord, \
		hit_point))) <= 0.0)
		return (phong_ambient(scene->amb_light, base));
	return (phong_color(scene, base, dot_product(normal, hit_point_to_light)));
/*	return create_trgb(0,
			(scene->amb_light->color.r + base.r) / 255 * scene->amb_light->ratio + (scene->light->color.r * base.r * dot_product(normal, hit_point_to_light) / 255) *scene->light->ratio, //+  specular * (scene->light->color.r - base.r),
			(scene->amb_light->color.g + base.g) / 255 * scene->amb_light->ratio + (scene->light->color.g * base.g * dot_product(normal, hit_point_to_light) / 255) *scene->light->ratio, //+  specular * (scene->light->color.g - base.g),
			(scene->amb_light->color.b + base.b) / 255 * scene->amb_light->ratio + (scene->light->color.b * base.b * dot_product(normal, hit_point_to_light) / 255) *scene->light->ratio //+  specular * (scene->light->color.b - base.b)
			);*/
}

t_color	get_color_sphere(t_scene *scene, void *object)
{
	t_sphere	*sphere;

	(void)scene;
	sphere = (t_sphere *)object;
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
