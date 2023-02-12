/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 18:52:21 by ncotte            #+#    #+#             */
/*   Updated: 2023/02/10 18:52:23 by ncotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_matrix	new_matrix(t_point a, t_point b, t_point c)
{
	t_matrix	matrix;

	matrix.a = a;
	matrix.b = b;
	matrix.c = c;
	return (matrix);
}

t_point	matrix_vector_multi(t_matrix matrix, t_point vector)
{
	t_point	result;

	result.x = dot_product(matrix.a, vector);
	result.y = dot_product(matrix.b, vector);
	result.z = dot_product(matrix.c, vector);
	return (result);
}

t_matrix	matrix_rotation_relative(t_point vector, double s)
{
	t_matrix	matrix;
	double		c;
	double		xy;
	double		yz;
	double		zx;

	c = cos_rot_1();
	xy = vector.x * vector.y * c;
	yz = vector.y * vector.z * c;
	zx = vector.z * vector.x * c;
	matrix = new_matrix(new_point(vector.x * vector.x * c, xy, zx), \
        new_point(xy, vector.y * vector.y * c, yz), \
        new_point(zx, yz, vector.z * vector.z * c));
	c = cos_rot();
	yz = vector.x * s;
	zx = vector.y * s;
	xy = vector.z * s;
	matrix.a.x += c;
	matrix.a.y -= xy;
	matrix.a.z += zx;
	matrix.b.x += xy;
	matrix.b.y += c;
	matrix.b.z -= yz;
	matrix.c.x -= zx;
	matrix.c.y += yz;
	matrix.c.z += c;
	return (matrix);
}
