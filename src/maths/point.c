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

t_point	new_point(double x, double y, double z)
{
	t_point	point;

	point.x = x;
	point.y = y;
	point.z = z;
	return (point);
}

double	distance_square(t_point a, t_point b)
{
	return (norm_square(sub_vectors(a, b)));
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

t_point	scalar_multi(double lambda, t_point vector)
{
	t_point	lambda_vector;

	lambda_vector.x = vector.x * lambda;
	lambda_vector.y = vector.y * lambda;
	lambda_vector.z = vector.z * lambda;
	return (lambda_vector);
}
