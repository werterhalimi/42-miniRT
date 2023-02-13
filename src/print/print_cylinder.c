/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 14:36:28 by ncotte            #+#    #+#             */
/*   Updated: 2023/02/12 23:19:15 by shalimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static double	cylinder_end_camera(t_cylinder *cylinder, t_point ray, double div)
{
	double	t1;
	double	t2;

	t1 = cylinder->value_top / div;
	t2 = cylinder->value_down / div;
	if (norm_square(sub_vectors(scalar_multi(t1, ray), \
		cylinder->relative_center_top)) > cylinder->radius_2)
		t1 = INFINITY;
	if (norm_square(sub_vectors(scalar_multi(t2, ray), \
		cylinder->relative_center_down)) > cylinder->radius_2)
		t2 = INFINITY;
	if (isfinite(t1) && t1 >= 0.0 && t1 < t2)
		return (t1);
	if (isfinite(t2) && t2 >= 0.0)
		return (t2);
	return (INFINITY);
}

static double	cylinder_side_camera(t_cylinder *cylinder, t_point ray)
{
	double	t1;
	double	t2;
	double	limit;
	double	value;

	value = dot_product(ray, cylinder->direction);
	t1 = quad_solv(1 - value * value, 2.0 * (dot_product(ray, \
		cylinder->relative_coord) - value * cylinder->value), \
		cylinder->value_quad, &t2);
	if (!isnan(t1))
	{
		value = dot_product(ray, cylinder->vector_semi_height);
		limit = t1 * value + cylinder->value_semi_height;
		if (t1 >= 0.0 && -(cylinder->semi_height_2) < limit \
			&& limit < cylinder->semi_height_2 && t1 < t2)
			return (t1);
		limit = t2 * value + cylinder->value_semi_height;
		if (t2 >= 0.0 && -(cylinder->semi_height_2) < limit \
			&& limit < cylinder->semi_height_2)
			return (t2);
	}
	return (INFINITY);
}

static double	cylinder_end(t_cylinder *cylinder, t_point ray, double div, t_point origin)
{
	double	t1;
	double	t2;
	t_point	oct;
	t_point	ocd;

	oct = sub_vectors(origin, cylinder->center_top);
	ocd = sub_vectors(origin, cylinder->center_down);
	t1 = dot_product(oct, cylinder->direction);
	t2 = dot_product(ocd, cylinder->direction);
	t1 /= div;
	t2 /= div;
	if (norm_square(sub_vectors(scalar_multi(t1, ray), oct)) > cylinder->radius_2)
		t1 = INFINITY;
	if (norm_square(sub_vectors(scalar_multi(t2, ray), ocd)) > cylinder->radius_2)
		t2 = INFINITY;
	if (isfinite(t1) && t1 >= 0.0 && t1 < t2)
		return (t1);
	if (isfinite(t2) && t2 >= 0.0)
		return (t2);
	return (INFINITY);
}

static double	cylinder_side(t_cylinder *cy, t_point ray, t_point origin)
{
	double	t1;
	double	t2;
	double	limit;
	double	value;
	double	value_sh;

	value = dot_product(ray, cy->direction);
	t1 = dot_product(origin, cy->direction);
	limit = norm_square(origin) - t1 * t1 - cy->radius_2;
	value_sh = dot_product(origin, cy->vector_semi_height);
	t1 = quad_solv(1 - value * value, 2.0 * (dot_product(ray, origin) - value * t1), limit, &t2);
	if (!isnan(t1))
	{
		value = dot_product(ray, cy->vector_semi_height);
		limit = t1 * value + value_sh;
		if (t1 >= 0.0 && -(cy->semi_height_2) < limit && limit < cy->semi_height_2 && t1 < t2)
			return (t1);
		limit = t2 * value + value_sh;
		if (t2 >= 0.0 && -(cy->semi_height_2) < limit && limit < cy->semi_height_2)
			return (t2);
	}
	return (INFINITY);
}

double	intersect_cylinder(t_point ray, void *object, t_point *origin)
{
	t_cylinder	*cylinder;
	double		div;
	double		t1;
	double		t2;

	cylinder = (t_cylinder *)object;
	t1 = INFINITY;
	t2 = INFINITY;
	div = dot_product(ray, cylinder->direction);
	if (div && origin)
		t1 = cylinder_end(cylinder, ray, div, *origin);
	else if (div)
		t1 = cylinder_end_camera(cylinder, ray, div);
	if (-1.0 != div && div != 1.0 && origin)
		t2 = cylinder_side(cylinder, ray, sub_vectors(*origin, cylinder->coord));
	else if (-1.0 != div && div != 1.0)
		t2 = cylinder_side_camera(cylinder, ray);
	if (isfinite(t1) && t1 >= 0.0 && t1 < t2)
		return (t1);
	if (isfinite(t2) && t2 >= 0.0)
		return (t2);
	return (INFINITY);
}
