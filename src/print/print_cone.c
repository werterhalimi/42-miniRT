/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_cone.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 17:04:57 by ncotte            #+#    #+#             */
/*   Updated: 2023/02/25 19:53:57 by shalimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static t_color	cone_map(t_texture *tex, double longitude, double h)
{
	double	tu;
	double	tv;

	tu = h;
	tv = longitude * MC_1_2PI + 0.25;
	return (tex->pixels[(int)(tu * tex->height)][(int)(tv * tex->width)]);
}

static t_color	get_uv_color(t_cone *cone, t_texture *tex, \
					t_point hit_point)
{
	double		tu;
	double		tv;
	double		longitude;
	t_point		vector;

	vector = sub_vectors(hit_point, cone->coord);
	longitude = get_longitude(vector, cone->right, cone->down);
	tu = 0.5 * dot_product(vector, cone->direction) + 0.5;
	tv = longitude * MC_1_2PI + 0.25;
	return (tex->pixels[(int)(tu * tex->height)][(int)(tv * tex->width)]);
}

static t_color	find_cone_color(t_object *object, double longitude, \
		double h, t_cone *cone)
{
	if (object->texture)
		return (cone_map(object->texture, longitude, h / cone->height));
	if (!((long)floor(h) % 2) ^ !((long)floor(longitude * MC_8_PI) % 2))
		return (*object->color_bis);
	return (cone->ratio_color);
}

t_color	get_color_cone(t_scene *scene, t_object *object, \
			t_point hit_point, t_point normal)
{
	t_cone	*cone;
	t_point	vector;
	double	h;
	double	longitude;

	(void) scene;
	(void) normal;
	cone = (t_cone *)object->object;
	if (!object->color_bis && !object->texture)
		return (cone->ratio_color);
	vector = sub_vectors(hit_point, cone->coord);
	longitude = get_longitude(vector, cone->right, cone->down);
	h = dot_product(vector, cone->direction);
	if (h < cone->height - FLT_EPSILON)
		return (find_cone_color(object, longitude, h, cone));
	if (object->color_bis && !((long)floor(sqrt(distance_square(vector, \
		scalar_multi(h, cone->direction)))) % 2) \
		^ !((long) floor(longitude * MC_8_PI) % 2))
		return (*object->color_bis);
	return (cone->ratio_color);
}

t_point	normal_cone(t_point ray, t_point hit_point, \
			t_object *object, t_texture *texture)
{
	t_cone	*cone;
	t_point	normal;
	t_point	chp;
	t_point	y;
	double	t;

	(void) texture;
	cone = (t_cone *)object->object;
	chp = (sub_vectors(hit_point, cone->coord));
	t = norm_square(chp) / dot_product(chp, cone->direction);
	y = add_vectors(cone->coord, scalar_multi(t, cone->direction));
	normal = unit_dist(hit_point, y);
	if (texture)
		normal = bump_normal(object->relief, normal, \
				get_uv_color(cone, texture, hit_point));
	if (dot_product(unit_dist(hit_point, cone->center_base), \
		cone->direction) >= -0.01)
		normal = cone->direction;
	if (dot_product(normal, ray) <= 0.0)
		return (normal);
	return (scalar_multi(-1.0, normal));
}
