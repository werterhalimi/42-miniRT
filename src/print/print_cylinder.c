/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 14:36:28 by ncotte            #+#    #+#             */
/*   Updated: 2023/02/23 18:57:48 by shalimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static t_color	cylinder_map(t_texture *tex, double longitude, double h)
{
	double	tu;
	double	tv;

	tu = 0.5 * h + 0.5;
	tv = longitude * MC_1_2PI + 0.25;
	return (tex->pixels[(int)(tu * tex->height)][(int)(tv * tex->width)]);
}

static t_color	get_uv_color(t_cylinder *cy, t_texture *tex, \
					t_point hit_point)
{
	double		tu;
	double		tv;
	double		longitude;
	t_point		vector;

	vector = sub_vectors(hit_point, cy->coord);
	longitude = (atan(dot_product(vector, cy->down) \
		/ dot_product(vector, cy->right)));
	if (dot_product(vector, cy->right) < 0)
		longitude += M_PI;
	tu = 0.5 * dot_product(vector, cy->direction) + 0.5;
	tv = longitude * MC_1_2PI + 0.25;
	return (tex->pixels[(int)(tu * tex->height)][(int)(tv * tex->width)]);
}

t_color	get_color_cylinder(t_scene *scene, t_object *object, \
			t_point hit_point, t_point normal)
{
	t_cylinder	*cylinder;
	t_point		vector;
	double		longitude;
	double		h;

	(void) scene;
	(void) normal;
	cylinder = (t_cylinder *)object->object;
	if (!object->color_bis && !object->texture)
		return (cylinder->ratio_color);
	vector = sub_vectors(hit_point, cylinder->coord);
	longitude = atan(dot_product(vector, cylinder->down) \
		/ dot_product(vector, cylinder->right));
	if (dot_product(vector, cylinder->right) < 0)
		longitude += M_PI;
	h = dot_product(vector, cylinder->direction);
	if (-(cylinder->semi_height - FLT_EPSILON) < h \
		&& h < cylinder->semi_height - FLT_EPSILON)
	{
		if (object->texture)
			return cylinder_map(object->texture, longitude, h / cylinder->semi_height);
		if (!((long)floor(h) % 2) ^ !((long)floor(longitude * MC_8_PI) % 2))
			return (*object->color_bis);
		return (cylinder->ratio_color);
	}
	if (object->color_bis && !((long)floor(sqrt(distance_square(vector, \
		scalar_multi(h, cylinder->direction)))) % 2) ^ !((long)floor(longitude * MC_8_PI) % 2))
		return (*object->color_bis);
	return (cylinder->ratio_color);
}

t_point	normal_cylinder(t_point ray, t_point hit_point, \
			void *object, t_texture *texture)
{
	t_cylinder	*cylinder;
	t_point		normal;
	t_point		projection;
	t_point		perturbation;
	t_color		color;

	(void) texture;
	cylinder = (t_cylinder *)object;
	projection = get_projection_unit(sub_vectors(hit_point, \
		cylinder->coord), cylinder->direction);
	if (norm_square(projection) >= cylinder->semi_height_2 - FLT_EPSILON)
	{
		if ((dot_product(projection, cylinder->direction) <= 0.0) \
			!= (dot_product(projection, ray) >= 0.0))
			return (scalar_multi(-1.0, cylinder->direction));
		return (cylinder->direction);
	}
	normal = unit_dist(hit_point, \
		add_vectors(projection, cylinder->coord));
	if (texture)
	{
		color = get_uv_color(cylinder, texture, hit_point);
		perturbation = (t_point){color.r - 0.5, color.g - 0.5, color.b - 0.5};
		perturbation = scalar_multi(0.9, perturbation);
		normal = unit_vector(add_vectors(perturbation, normal));
	}

	if (dot_product(normal, ray) > 0.0)
		normal = scalar_multi(-1.0, normal);
	return (normal);
}
