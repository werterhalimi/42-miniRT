/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 22:18:57 by shalimi           #+#    #+#             */
/*   Updated: 2023/02/25 19:20:37 by shalimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	init_phong(t_scene *scene, t_phong *phong, t_point origin)
{
	t_color	amb_color;

	amb_color = scene->amb_light->ratio_color;
	phong->hit_point = add_vectors(origin, \
		scalar_multi(phong->view_ray_dist, phong->view_ray));
	phong->normal = phong->object->get_normal(phong->view_ray, \
		phong->hit_point, phong->object, phong->object->normal_map);
	phong->object_color = phong->object->get_color(scene, phong->object, \
		phong->hit_point, phong->normal);
	phong->final_color.r = fmin(amb_color.r \
		* phong->object_color.r + phong->final_color.r, 1.0);
	phong->final_color.g = fmin(amb_color.g \
		* phong->object_color.g + phong->final_color.g, 1.0);
	phong->final_color.b = fmin(amb_color.b \
		* phong->object_color.b + phong->final_color.b, 1.0);
}

void	set_phong(t_phong *phong, t_point coord, t_color color)
{
	t_point	light_ray;

	phong->light_coord = coord;
	phong->light_color = color;
	light_ray = sub_vectors(phong->light_coord, phong->hit_point);
	phong->light_ray_dist_2 = norm_square(light_ray);
	phong->light_ray = unit_vector(light_ray);
	phong->dot_light_normal = dot_product(phong->light_ray, phong->normal);
}

static void	phong_specular(t_phong *phong, double dot)
{
	double	specular;

	if (dot <= 0.0 || phong->object->specular == 0.0)
		return ;
	specular = pow(dot, phong->object->specular);
	phong->final_color.r = fmin(phong->light_color.r \
		* specular + phong->final_color.r, 1.0);
	phong->final_color.g = fmin(phong->light_color.g \
		* specular + phong->final_color.g, 1.0);
	phong->final_color.b = fmin(phong->light_color.b \
		* specular + phong->final_color.b, 1.0);
}

void	phong_object(t_phong *phong)
{
	if (phong->object->type <= TYPE_SPOT_LIGHT \
		|| phong->dot_light_normal <= 0.0)
		return ;
	phong->final_color.r = fmin(phong->light_color.r \
		* phong->object_color.r * phong->dot_light_normal \
		+ phong->final_color.r, 1.0);
	phong->final_color.g = fmin(phong->light_color.g \
		* phong->object_color.g * phong->dot_light_normal \
		+ phong->final_color.g, 1.0);
	phong->final_color.b = fmin(phong->light_color.b \
		* phong->object_color.b * phong->dot_light_normal \
		+ phong->final_color.b, 1.0);
	phong_specular(phong, dot_product(phong->normal, \
		unit_vector(add_vectors(scalar_multi(-1.0, \
		phong->view_ray), phong->light_ray))));
}
