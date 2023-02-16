/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_plane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 14:36:36 by ncotte            #+#    #+#             */
/*   Updated: 2023/02/16 03:47:54 by shalimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	print_plane(t_phong *phong)
{
	if (dot_product(phong->normal, unit_vector(sub_vectors(phong->coord, \
		phong->hit_point))) <= 0.0)
		return ;
	(phong_diffuse(phong, dot_product(phong->normal, phong->light_ray)));
}

t_color	get_color_plane(t_scene *scene, void *object, \
			t_point hit_point, t_point normal)
{
	t_plane	*plane;
	t_point	vector;
	long	x;
	long	y;

	(void) scene;
	(void) normal;
	plane = (t_plane *)object;
	if (!plane->color_bis)
		return (plane->color);
	vector = sub_vectors(hit_point, plane->coord);
	x = (long)floor(dot_product(vector, plane->right));
	y = (long)floor(dot_product(vector, plane->down));
	if (!(x % 2) ^ !(y % 2))
		return (*plane->color_bis);
	return (plane->color);
}

t_point	normal_plane(t_point ray, t_point hit_point, void *object)
{
	t_plane	*plane;

	(void) hit_point;
	plane = (t_plane *)object;
	if (dot_product(plane->normal, ray) <= 0.0)
		return (plane->normal);
	return (scalar_multi(-1.0, plane->normal));
}
