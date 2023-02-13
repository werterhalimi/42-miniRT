/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 14:36:43 by ncotte            #+#    #+#             */
/*   Updated: 2023/02/12 23:55:52 by shalimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

double	intersect_sphere(t_point ray, void *object, t_point *origin)
{
	t_sphere	*sphere;
	t_point		oc;
	double		value;
	double		t1;
	double		t2;

	sphere = (t_sphere *)object;
	oc = sphere->relative_coord;
	value = sphere->value;
	if (origin)
	{
		oc = sub_vectors(*origin, sphere->coord);
		value = norm_square(oc) - sphere->radius_2;
	}
	t1 = quad_solv(1.0, 2.0 * dot_product(ray, oc), value, &t2);
	if (!isnan(t1) && t1 < t2 && t1 >= 0.0)
		return (t1);
	if (!isnan(t2) && t2 >= 0.0)
		return (t2);
	return (INFINITY);
}
