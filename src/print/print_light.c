/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 14:36:18 by ncotte            #+#    #+#             */
/*   Updated: 2023/02/12 21:40:03 by shalimi          ###   ########.fr       */
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
	t = oc.x / ray.x;
	if (is_null(add_vectors(scalar_multi(t, ray), oc)) && t >= 0.0)
		return (t);
	return (INFINITY);
}
