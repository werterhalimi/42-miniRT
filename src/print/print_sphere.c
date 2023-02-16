/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 14:36:43 by ncotte            #+#    #+#             */
/*   Updated: 2023/02/16 03:47:30 by shalimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

//	t_point h = unit_vector(add_vectors(scalar_multi(-1.0, ray), hit_point_to_light));
//	double specular = pow(dot_product(phong.normal, h), 25);
void	print_sphere(t_phong *phong)
{
	if (dot_product(phong->normal, unit_vector(sub_vectors(phong->coord, \
		phong->hit_point))) <= 0.0)
		return ;
	phong_diffuse(phong, dot_product(phong->normal, phong->light_ray));
}

t_color	get_color_sphere(t_scene *scene, void *object)
{
	t_sphere	*sphere;

	(void) scene;
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
