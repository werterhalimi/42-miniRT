/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_plane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 14:36:36 by ncotte            #+#    #+#             */
/*   Updated: 2023/02/25 19:21:39 by shalimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static t_color	plane_map(t_texture *tex, double x, double y)
{
	double	tu;
	double	tv;

	tu = y - floor(y);
	tv = x - floor(x);
	return (tex->pixels[(int)(tu * tex->height)][(int)(tv * tex->width)]);
}

static t_color	get_uv_color(t_plane *plane, t_texture *tex, \
					t_point hit_point)
{
	double		tu;
	double		tv;
	double		x;
	double		y;
	t_point		vector;

	vector = sub_vectors(hit_point, plane->coord);
	x = (dot_product(vector, plane->right));
	y = (dot_product(vector, plane->down));
	tu = y - floor(y);
	tv = x - floor(x);
	return (tex->pixels[(int)(tu * tex->height)][(int)(tv * tex->width)]);
}

t_color	get_color_plane(t_scene *scene, t_object *object, \
			t_point hit_point, t_point normal)
{
	t_plane	*plane;
	t_point	vector;
	double	x;
	double	y;

	(void) scene;
	(void) normal;
	plane = (t_plane *)object->object;
	if (!object->color_bis && !object->texture)
		return (plane->ratio_color);
	vector = sub_vectors(hit_point, plane->coord);
	x = (dot_product(vector, plane->right));
	y = (dot_product(vector, plane->down));
	if (object->texture)
		return (plane_map(object->texture, x, y));
	if (!((long)floor(x) % 2) ^ !((long)floor(y) % 2))
		return (*object->color_bis);
	return (plane->ratio_color);
}

t_point	normal_plane(t_point ray, t_point hit_point, \
			t_object *object, t_texture *texture)
{
	t_plane	*plane;
	t_color	color;
	t_point	normal;

	plane = (t_plane *)object->object;
	normal = plane->normal;
	if (texture)
	{
		color = get_uv_color(plane, texture, hit_point);
		normal = bump_normal(object->relief, normal, color);
	}
	if (dot_product(normal, ray) <= 0.0)
		return (normal);
	return (scalar_multi(-1.0, normal));
}
