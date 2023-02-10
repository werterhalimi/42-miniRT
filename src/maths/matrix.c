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
