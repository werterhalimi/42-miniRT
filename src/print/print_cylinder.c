/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 14:36:28 by ncotte            #+#    #+#             */
/*   Updated: 2023/02/13 22:57:28 by shalimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
unsigned int	print_cylinder(t_scene *scene, t_cylinder *cy \
		, t_point hit_point, t_point hit_point_to_light)
{
	t_color	base;
	double	angle2;
	t_point	rebound;
	t_point	normal;

	normal = add_vectors(get_projection_unit(sub_vectors(hit_point, cy->coord), cy->direction), cy->coord);
	normal = unit_vector(sub_vectors(hit_point,normal));
	if (distance_square(hit_point, cy->center_top) <= cy->radius_2)
			normal = cy->direction;
	if (distance_square(hit_point, cy->center_down) <= cy->radius_2)
			normal = scalar_multi(-1.0, cy->direction);
	angle2 = vector_angle(normal, unit_vector(sub_vectors(scene->light->coord, hit_point)));
	rebound = reflection(sub_vectors(hit_point, scene->light->coord), normal);
	base= cy->color;
	if (angle2 >= M_PI_2)
		return create_trgb(0,
				(scene->amb_light->color.r + base.r) / 255 * scene->amb_light->ratio,
				(scene->amb_light->color.g + base.g) / 255 * scene->amb_light->ratio,
				(scene->amb_light->color.b + base.b) / 255 * scene->amb_light->ratio
				);
	return phong_color(scene, base, dot_product(normal, hit_point_to_light));
}

static double	cylinder_end_camera(t_cylinder *cy, t_point ray, double div)
{
	double	t1;
	double	t2;

	t1 = cy->value_top / div;
	t2 = cy->value_down / div;
	if (norm_square(sub_vectors(scalar_multi(t1, ray), \
		cy->relative_center_top)) > cy->radius_2)
		t1 = INFINITY;
	if (norm_square(sub_vectors(scalar_multi(t2, ray), \
		cy->relative_center_down)) > cy->radius_2)
		t2 = INFINITY;
	if (isfinite(t1) && t1 >= 0.0 && t1 < t2)
		return (t1);
	if (isfinite(t2) && t2 >= 0.0)
		return (t2);
	return (INFINITY);
}

static double	cylinder_side_camera(t_cylinder *cylinder, t_point ray, double div)
{
	double	t1;
	double	t2;
	double	limit;
	double	value;

	t1 = quad_solv(1 - div * div, 2.0 * (dot_product(ray, \
		cylinder->relative_coord) - div * cylinder->value), \
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

static double	cylinder_end(t_cylinder *cy, t_point ray, \
					double div, t_point origin)
{
	double	t1;
	double	t2;
	t_point	oct;
	t_point	ocd;

	oct = sub_vectors(cy->center_top, origin);
	ocd = sub_vectors(cy->center_down, origin);
	t1 = dot_product(oct, cy->direction) / div;
	t2 = dot_product(ocd, cy->direction) / div;
	if (norm_square(sub_vectors(scalar_multi(t1, ray), oct)) > cy->radius_2)
		t1 = INFINITY;
	if (norm_square(sub_vectors(scalar_multi(t2, ray), ocd)) > cy->radius_2)
		t2 = INFINITY;
	if (isfinite(t1) && t1 >= 0.0 && t1 < t2)
		return (t1);
	if (isfinite(t2) && t2 >= 0.0)
		return (t2);
	return (INFINITY);
}

static double	cylinder_side(t_cylinder *cy, t_point ray, \
					double div, t_point origin)
{
	double	t1;
	double	t2;
	double	limit;
	double	value;
	double	value_sh;

	t1 = dot_product(origin, cy->direction);
	limit = norm_square(origin) - t1 * t1 - cy->radius_2;
	value_sh = dot_product(origin, cy->vector_semi_height);
	t1 = quad_solv(1 - div * div, 2.0 * (dot_product(ray, \
		origin) - div * t1), limit, &t2);
	if (!isnan(t1))
	{
		value = dot_product(ray, cy->vector_semi_height);
		limit = t1 * value + value_sh;
		if (t1 >= 0.0 && -(cy->semi_height_2) < limit \
			&& limit < cy->semi_height_2 && t1 < t2)
			return (t1);
		limit = t2 * value + value_sh;
		if (t2 >= 0.0 && -(cy->semi_height_2) < limit \
			&& limit < cy->semi_height_2)
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
		t2 = cylinder_side(cylinder, ray, div, \
			sub_vectors(*origin, cylinder->coord));
	else if (-1.0 != div && div != 1.0)
		t2 = cylinder_side_camera(cylinder, ray, div);
	if (isfinite(t1) && t1 >= 0.0 && t1 < t2)
		return (t1);
	if (isfinite(t2) && t2 >= 0.0)
		return (t2);
	return (INFINITY);
}
