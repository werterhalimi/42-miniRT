/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cone.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 13:47:08 by ncotte            #+#    #+#             */
/*   Updated: 2023/02/17 16:40:28 by shalimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

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
		if (limit <= 0.0 || cone->height_2 <= limit)
			t1 = INFINITY;
		limit = t2 * value + cone->value_height;
		if (limit <= 0.0 || cone->height_2 <= limit)
			t2 = INFINITY;
		if (isfinite(t1) && t1 >= 0.0 && (t1 < t2 || t2 <= 0.0))
			return (t1);
		if ((isfinite(t2) && t2 >= 0.0))
			return (t2);
	}
	return (INFINITY);
}

static double	cone_end(t_cone *co, t_point ray, double div, t_point *origin)
{
	double	t1;
	t_point	ocb;

	t1 = co->value_base;
	ocb = co->relative_center_base;
	if (origin)
	{
		ocb = sub_vectors(co->center_base, *origin);
		t1 = dot_product(ocb, co->direction);
	}
	t1 /= div;
	if (distance_square(scalar_multi(t1, ray), ocb) > co->radius_2)
		t1 = INFINITY;
	if (isfinite(t1) && t1 >= 0.0)
		return (t1);
	return (INFINITY);
}

static double	cone_side(t_cone *co, t_point ray, double div, t_point origin)
{
	double	t1;
	double	t2;
	double	limit;
	double	value;
	double	value_sh;

	value = dot_product(origin, co->direction);
	t1 = quad_solv(1 - div * div * co->ratio, 2.0 * (dot_product(ray, \
		origin) - co->ratio * div * value), \
		norm_square(origin) - co->ratio * value * value, &t2);
	if (isnan(t1))
		return (INFINITY);
	value_sh = dot_product(origin, co->vector_height);
	value = dot_product(ray, co->vector_height);
	limit = t1 * value + value_sh;
	if (limit <= 0.0 || co->height_2 <= limit)
		t1 = INFINITY;
	limit = t2 * value + value_sh;
	if (limit <= 0.0 || co->height_2 <= limit)
		t2 = INFINITY;
	if (isfinite(t1) && t1 >= 0.0 && (t1 < t2 || t2 <= 0.0))
		return (t1);
	if ((isfinite(t2) && t2 >= 0.0))
		return (t2);
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
	if (div)
		t1 = cone_end(cone, ray, div, origin);
	if (origin)
		t2 = cone_side(cone, ray, div, \
			sub_vectors(*origin, cone->coord));
	else
		t2 = cone_side_camera(cone, ray, div);
	if (isfinite(t1) && t1 >= 0.0 && (t1 < t2 || t2 <= 0.0))
		return (t1);
	if (isfinite(t2) && t2 >= 0.0)
		return (t2);
	return (INFINITY);
}
