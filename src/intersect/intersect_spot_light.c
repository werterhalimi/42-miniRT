/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_spot_light.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 11:57:00 by ncotte            #+#    #+#             */
/*   Updated: 2023/02/16 11:57:02 by ncotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

double	intersect_spot_light(t_point ray, void *object, t_point *origin)
{
	t_spot_light	*spot_light;
	t_point			oc;
	double			t;

	spot_light = (t_spot_light *)object;
	oc = spot_light->relative_coord;
	if (origin)
		oc = sub_vectors(spot_light->coord, *origin);
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
