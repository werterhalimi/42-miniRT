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

static double	cylinder_end(t_cylinder *cylinder, t_point ray, double div, t_point *origin)
{
	double	t1;
	double	t2;
	t_point	oct;
	t_point	ocd;
	double	value[2];

	if (origin)
	{
		oct = sub_vectors(*origin, cylinder->center_top);
		ocd = sub_vectors(*origin, cylinder->center_down);
		value[0] = dot_product(oct, cylinder->direction);
		value[1] = dot_product(ocd, cylinder->direction);
	}
	else
	{
		oct = cylinder->relative_center_top;
		ocd = cylinder->relative_center_down;
		value[0] = cylinder->value_top;
		value[1] = cylinder->value_down;
	}
	t1 = value[0] / div;
	t2 = value[1] / div;
	if (norm_square(sub_vectors(scalar_multi(t1, ray), \
		oct)) > cylinder->radius_square)
		t1 = INFINITY;
	if (norm_square(sub_vectors(scalar_multi(t2, ray), \
		ocd)) > cylinder->radius_square)
		t2 = INFINITY;
	if (isfinite(t1) && t1 >= 0.0 && t1 < t2)
		return (t1);
	if (isfinite(t2) && t2 >= 0.0)
		return (t2);
	return (INFINITY);
}

static double	cylinder_side(t_cylinder *cylinder, t_point ray, t_point *origin)
{
	double	t1;
	double	t2;
	double	limit;
	double	value;
	t_point		oc;

	if (origin)
	{
		oc = sub_vectors(*origin, cylinder->coord);
	}
	else
	{
		oc = cylinder->relative_coord;
	}
	value = dot_product(ray, cylinder->direction);
	t1 = quad_solv(1 - value * value, 2.0 * (dot_product(ray, \
		oc) - value * dot_product(oc, cylinder->direction)), \
		(norm_square(oc) \
			- dot_product(oc, cylinder->direction) * dot_product(oc, cylinder->direction) - cylinder->radius_square), &t2);
	if (!isnan(t1))
	{
		value = dot_product(ray, cylinder->vector_semi_height);
		limit = t1 * value + dot_product(oc, cylinder->vector_semi_height); 
		if (t1 >= 0.0 && -(cylinder->semi_height_square) < limit \
			&& limit < cylinder->semi_height_square && t1 < t2)
			return (t1);
		limit = t2 * value + dot_product(oc, cylinder->vector_semi_height);
		if (t2 >= 0.0 && -(cylinder->semi_height_square) < limit \
			&& limit < cylinder->semi_height_square)
			return (t2);
	}
	return (INFINITY);
}

double	intersect_cylinder(t_point ray, void *object)
{
	t_cylinder	*cylinder;
	double		div;
	double		t1;
	double		t2;

	t1 = INFINITY;
	t2 = INFINITY;
	cylinder = (t_cylinder *)object;
	div = dot_product(ray, cylinder->direction);
	if (div)
		t1 = cylinder_end(cylinder, ray, div,0);
	if (-1.0 != div && div != 1.0)
		t2 = cylinder_side(cylinder, ray, 0);
	if (isfinite(t1) && t1 >= 0.0 && t1 < t2)
		return (t1);
	if (isfinite(t2) && t2 >= 0.0)
		return (t2);
	return (INFINITY);
}

double	intersect_cylinder_absolute(t_point ray, void *object, t_point origin)
{
	t_cylinder	*cylinder;
	double		div;
	double		t1;
	double		t2;

	cylinder = (t_cylinder *)object;
	t1 = INFINITY;
	t2 = INFINITY;
	div = dot_product(ray, cylinder->direction);
	if (div)
		t1 = cylinder_end(cylinder, ray, div, &origin);
	if (-1.0 != div && div != 1.0)
		t2 = cylinder_side(cylinder, ray, &origin);
	if (isfinite(t1) && t1 >= 0.0 && t1 < t2)
		return (t1);
	if (isfinite(t2) && t2 >= 0.0)
		return (t2);
	return (INFINITY);
}

unsigned int	get_color_cylinder(t_scene *scene, void *object)
{
	t_cylinder	*cylinder;

	(void)scene;
	cylinder = (t_cylinder *)object;
	return (color_trgb(cylinder->color));
}
