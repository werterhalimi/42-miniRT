/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_plane.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 13:47:03 by ncotte            #+#    #+#             */
/*   Updated: 2023/02/14 13:47:05 by ncotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

double	intersect_plane(t_point ray, void *object, t_point *origin)
{
	t_plane	*plane;
	double	value;
	double	div;
	double	t;

	plane = (t_plane *)object;
	div = dot_product(ray, plane->normal);
	if (!div)
		return (INFINITY);
	value = plane->value;
	if (origin)
		value = dot_product(sub_vectors(plane->coord, *origin), plane->normal);
	t = value / div;
	if (t < 0.0)
		return (INFINITY);
	return (t);
}
