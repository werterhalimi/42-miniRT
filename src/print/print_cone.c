/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_cone.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 17:04:57 by ncotte            #+#    #+#             */
/*   Updated: 2023/02/13 23:22:57 by shalimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

unsigned int	print_cone(t_scene *scene, t_cone *cone \
		, t_point hit_point, t_point hit_point_to_light)
{
	t_color	base;
	double	angle2;
	t_point	rebound;
	t_point	normal;

	normal = add_vectors(get_projection_unit(sub_vectors(hit_point, cone->coord), cone->direction), cone->coord);
	normal = unit_vector(sub_vectors(hit_point,normal));
	if (distance_square(hit_point, cone->center_base) == cone->radius_2)
			normal = scalar_multi(-1.0, cone->direction);
	angle2 = vector_angle(normal, unit_vector(sub_vectors(scene->light->coord, hit_point)));
	rebound = reflection(sub_vectors(hit_point, scene->light->coord), normal);
	base= cone->color;
	if (angle2 >= M_PI_2)
		return create_trgb(0,
				(scene->amb_light->color.r + base.r) / 255 * scene->amb_light->ratio,
				(scene->amb_light->color.g + base.g) / 255 * scene->amb_light->ratio,
				(scene->amb_light->color.b + base.b) / 255 * scene->amb_light->ratio
				);
	return phong_color(scene, base, dot_product(normal, hit_point_to_light));
}

static double	cone_end_camera(t_cone *co, t_point ray, double div)
{
	double	t1;

	t1 = co->value_base / div;
	if (norm_square(sub_vectors(scalar_multi(t1, ray), \
		co->relative_center_base)) > co->radius_2)
		t1 = INFINITY;
	if (isfinite(t1) && t1 >= 0.0)
		return (t1);
	return (INFINITY);
}

static double	cone_side_camera(t_cone *cone, t_point ray, double div)
{
	double	t1;
	double	t2;
	double	limit;
	double	value;

	t1 = quad_solv(1 - div * div * cone->ratio, 2.0 * (dot_product(ray, \
		cone->relative_coord) - cone->ratio * div * cone->value), \
		cone->value_quad, &t2);
	if (!isnan(t1))
	{
		value = dot_product(ray, cone->vector_height);
		limit = t1 * value + cone->value_height;
		if (t1 >= 0.0 && 0.0 < limit && limit < cone->height_2 && t1 < t2)
			return (t1);
		limit = t2 * value + cone->value_height;
		if (t2 >= 0.0 && 0.0 < limit && limit < cone->height_2)
			return (t2);
	}
	return (INFINITY);
}

static double	cone_end(t_cone *co, t_point ray, \
					double div, t_point origin)
{
	double	t1;
	t_point	ocb;

	ocb = sub_vectors(co->center_base, origin);
	t1 = dot_product(ocb, co->direction) / div;
	if (norm_square(sub_vectors(scalar_multi(t1, ray), ocb)) > co->radius_2)
		t1 = INFINITY;
	if (isfinite(t1) && t1 >= 0.0)
		return (t1);
	return (INFINITY);
}

static double	cone_side(t_cone *co, t_point ray, \
					double div, t_point origin)
{
	double	t1;
	double	t2;
	double	limit;
	double	value;
	double	value_sh;

	t1 = dot_product(origin, co->direction);
	limit = norm_square(origin) - t1 * t1 - co->radius_2;
	value_sh = dot_product(origin, co->vector_height);
	t1 = quad_solv(1 - div * div, 2.0 * (dot_product(ray, \
		origin) - div * t1), limit, &t2);
	if (!isnan(t1))
	{
		value = dot_product(ray, co->vector_height);
		limit = t1 * value + value_sh;
		if (t1 >= 0.0 && 0.0 < limit && limit < co->height_2 && t1 < t2)
			return (t1);
		limit = t2 * value + value_sh;
		if (t2 >= 0.0 && 0.0 < limit && limit < co->height_2)
			return (t2);
	}
	return (INFINITY);
}

double	intersect_cone(t_point ray, void *object, t_point *origin)
{
	t_cone	*cone;
	double	div;
	double	t1;
	double	t2;

	cone = (t_cone *)object;
	t1 = INFINITY;
	t2 = INFINITY;
	div = dot_product(ray, cone->direction);
	if (div && origin)
		t1 = cone_end(cone, ray, div, *origin);
	else if (div)
		t1 = cone_end_camera(cone, ray, div);
	if (origin)
		t2 = cone_side(cone, ray, div, \
			sub_vectors(*origin, cone->coord));
	else
		t2 = cone_side_camera(cone, ray, div);
	if (isfinite(t1) && t1 >= 0.0 && t1 < t2)
		return (t1);
	if (isfinite(t2) && t2 >= 0.0)
		return (t2);
	return (INFINITY);
}
