/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 13:59:46 by ncotte            #+#    #+#             */
/*   Updated: 2023/02/12 19:03:19 by shalimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_point	cross_product(t_point v1, t_point v2)
{
	t_point	vector;

	vector.x = v1.y * v2.z - v1.z * v2.y;
	vector.y = v1.z * v2.x - v1.x * v2.z;
	vector.z = v1.x * v2.y - v1.y * v2.x;
	return (vector);
}

double	dot_product(t_point v1, t_point v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

double	norm_square(t_point vector)
{
	return (dot_product(vector, vector));
}

t_point	unit_vector(t_point vector)
{
	return (scalar_multi(inv_sqrt(norm_square(vector)), vector));
}

t_point get_projection(t_point a, t_point b)
{
    double dot = dot_product(a, b);
    double norm_squared = norm_square(b);
    return scalar_multi(dot / norm_squared, b);
}

double	distance_square(t_point a, t_point b)
{
	return (
			(a.x - b.x) * (a.x - b.x) +
			(a.y - b.y) * (a.y - b.y) +
			(a.z - b.z) * (a.z - b.z)
		   );
}

t_point	orthogonal_base(t_point vector, t_point *orthogonal)
{
	t_point	tmp;

	tmp = vector;
	if (tmp.x || tmp.y)
		tmp.z += 1.0;
	else if (tmp.z > 0)
		tmp.x -= 1.0;
	else
		tmp.x += 1.0;
	*orthogonal = unit_vector(cross_product(vector, tmp));
	return (cross_product(vector, *orthogonal));
}
