/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 13:59:56 by ncotte            #+#    #+#             */
/*   Updated: 2023/01/30 13:59:58 by ncotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
/*
double	dist_op(t_point o, t_point p)
{
	return (norm_vector(sub_vectors(p, o)));
}
*/

int	is_null(t_point vector)
{
	return (!(vector.x || vector.y || vector.z));
}

t_point	new_point(double x, double y, double z)
{
	t_point	point;

	point.x = x;
	point.y = y;
	point.z = z;
	return (point);
}

t_point	add_vectors(t_point v1, t_point v2)
{
	t_point	vector;

	vector.x = v1.x + v2.x;
	vector.y = v1.y + v2.y;
	vector.z = v1.z + v2.z;
	return (vector);
}

t_point	sub_vectors(t_point v1, t_point v2)
{
	t_point	vector;

	vector.x = v1.x - v2.x;
	vector.y = v1.y - v2.y;
	vector.z = v1.z - v2.z;
	return (vector);
}
