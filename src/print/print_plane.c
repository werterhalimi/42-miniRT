/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_plane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 14:36:36 by ncotte            #+#    #+#             */
/*   Updated: 2023/02/17 21:04:02 by shalimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_color	get_color_plane(t_scene *scene, t_object *object, \
			t_point hit_point, t_point normal)
{
	t_plane	*plane;
	t_point	vector;
	long	x;
	long	y;

	(void) scene;
	(void) normal;
	plane = (t_plane *)object->object;
	if (!object->color_bis)
		return (plane->color);
	vector = sub_vectors(hit_point, plane->coord);
	x = (long)floor(dot_product(vector, plane->right));
	y = (long)floor(dot_product(vector, plane->down));
	if (!(x % 2) ^ !(y % 2))
		return (*object->color_bis);
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
