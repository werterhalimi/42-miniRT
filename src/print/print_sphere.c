/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 14:36:43 by ncotte            #+#    #+#             */
/*   Updated: 2023/02/22 18:11:41 by shalimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static t_color	sphere_map(t_texture *tex, double longitude, double latitude)
{
	double	tu;
	double	tv;

	tu = 1 - (latitude * M_1_PI + 0.5);
	tv = longitude * 0.5 * M_1_PI + 0.25;
	return (tex->pixels[(int)(tu * tex->height)][(int)(tv * tex->width)]);
}

static t_color	get_uv_color(t_sphere *sphere, t_texture *tex, t_point hit_point)
{
	double		tu;
	double		tv;
	double		longitude;
	double		latitude;
	t_point		vector;


	vector = sub_vectors(hit_point, sphere->coord);
	longitude = (atan(dot_product(vector, sphere->down) \
		/ dot_product(vector, sphere->right)));
	if (dot_product(vector, sphere->right) < 0)
		longitude += M_PI;
	latitude = (asin(dot_product(vector, sphere->front) \
		/ sphere->radius));



	tu = 1 - (latitude * M_1_PI + 0.5);
	tv = longitude * 0.5 * M_1_PI + 0.25;
	return (tex->pixels[(int)(tu * tex->height)][(int)(tv * tex->width)]);

}

t_color	get_color_sphere(t_scene *scene, t_object *object, \
			t_point hit_point, t_point normal)
{
	t_sphere	*sphere;
	t_point		vector;
	double		longitude;
	double		latitude;

	(void) scene;
	(void) normal;
	sphere = (t_sphere *)object->object;
	if (!object->color_bis && !object->texture)
		return (sphere->color);
	vector = sub_vectors(hit_point, sphere->coord);
	longitude = (atan(dot_product(vector, sphere->down) \
		/ dot_product(vector, sphere->right)));
	if (dot_product(vector, sphere->right) < 0)
		longitude += M_PI;
	latitude = (asin(dot_product(vector, sphere->front) \
		/ sphere->radius));
	if (object->texture)
		return (sphere_map(object->texture, longitude, latitude));
	if (!((long)floor(longitude * 8 * M_1_PI) % 2) ^ !((long)floor(latitude * 8 * M_1_PI) % 2))
		return (*object->color_bis);
	return (sphere->color);
}

t_point	normal_sphere(t_point ray, t_point hit_point, void *object, t_texture *texture)
{
	t_sphere	*sphere;
	t_point		normal;

	sphere = (t_sphere *)object;
	normal = unit_dist(hit_point, sphere->coord);
	if (texture)
	{
		t_color color = get_uv_color(sphere, texture, hit_point);
		t_point perturbation = (t_point) {color.r - 0.5, color.g - 0.5, color.b - 0.5};
		perturbation = scalar_multi(0.9, perturbation);
		normal = unit_vector(add_vectors(perturbation, normal));
	}
	if (dot_product(normal, ray) <= 0.0)
		return (normal);
	return (scalar_multi(-1.0, normal));
}
