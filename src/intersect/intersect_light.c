/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_light.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 13:46:57 by ncotte            #+#    #+#             */
/*   Updated: 2023/02/15 12:39:57 by shalimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

double	intersect_light(t_point ray, void *object, t_point *origin)
{
	t_light	*light;
	t_point	oc;
	double	t;

	light = (t_light *)object;
	oc = light->relative_coord;
	if (origin)
		oc = sub_vectors(light->coord, *origin);
	if (ray.x)
		t = oc.x / ray.x;
	else if (ray.y)
		t = oc.y / ray.y;
	else
		t = oc.z / ray.z;
	oc = sub_vectors(scalar_multi(t, ray), oc);
	if (!(oc.x || oc.y || oc.z) && t >= 0.0)
		return (t);
	return (INFINITY);
}
