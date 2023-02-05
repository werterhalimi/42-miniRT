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
/*
double	norm_vector(t_point front)
{
	return (sqrt(front.x * front.x + front.y * front.y \
		+ front.z * front.z));
}
*/
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

static int	set_coord(double *coord, char *item, char last)
{
	if (!item)
		return (print_error(ERROR, \
			"Invalid coordinate format. Expected: x,y,z"));
	if (str_to_d(item, coord, last))
		return (print_error(ERROR, \
			"The coordinate components must be a double"));
	if (*coord < -1.0 || 1.0 < *coord)
		return (print_error(ERROR, \
			"The coordinate components must be included in [-1.0; 1.0]"));
	return (SUCCESS);
}

int	parse_vector(t_point *vector, char *item, char norm)
{
	if (!item)
		return (print_error(ERROR, "A coordinate is missing"));
	if (set_coord(&vector->x, item, NO))
		return (ERROR);
	item = next_coord(item, NO);
	if (set_coord(&vector->y, item, NO))
		return (ERROR);
	item = next_coord(item, NO);
	if (set_coord(&vector->z, item, YES))
		return (ERROR);
	if (next_coord(item, YES))
		return (print_error(ERROR, "Too many coordinate components"));
	if (!(vector->x) && !(vector->y) && !(vector->z))
		return (print_error(ERROR, "The vector can not be null"));
	if (norm)
		*vector = unit_vector(*vector);
	return (SUCCESS);
}
