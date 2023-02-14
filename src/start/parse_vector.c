/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_vector.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 14:03:09 by ncotte            #+#    #+#             */
/*   Updated: 2023/02/09 14:03:10 by ncotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static int	set_coord(double *coord, char *item, char last)
{
	if (!item)
		return (print_error(ERROR, \
			"Invalid coordinate format. Expected: x,y,z"));
	if (str_to_double(item, coord, last))
		return (print_error(ERROR, \
			"The coordinate components must be a double"));
	if (*coord < -1.0 || 1.0 < *coord)
		return (print_error(ERROR, \
			"The coordinate components must be included in [-1.0; 1.0]"));
	return (SUCCESS);
}

int	parse_vector(t_point *vector, char *item, char unit)
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
		return (print_error(ERROR, "The normal can not be null"));
	if (unit)
		*vector = unit_vector(*vector);
	return (SUCCESS);
}
