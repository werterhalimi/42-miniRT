/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   front.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 13:59:46 by ncotte            #+#    #+#             */
/*   Updated: 2023/01/30 13:59:48 by ncotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

//double	norm_vector(t_point normal)
//{
//	return (sqrt(normal.x * normal.x + normal.y * normal.y \
//		+ normal.z * normal.z));
//}

t_point	scalar_multi(double lambda, t_point vector)
{
	t_point	lambda_vector;

	lambda_vector.x = vector.x * lambda;
	lambda_vector.y = vector.y * lambda;
	lambda_vector.z = vector.z * lambda;
	return (lambda_vector);
}

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
