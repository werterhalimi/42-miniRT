/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_coord.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 13:58:05 by ncotte            #+#    #+#             */
/*   Updated: 2023/02/09 13:58:06 by ncotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

char	*next_coord(char *item, char last)
{
	if (*item == '-')
		item++;
	while (ft_isdigit(*item))
		item++;
	if (*item == '.')
		item++;
	while (ft_isdigit(*item))
		item++;
	if (last && (!(*item) || *item == '\n' || *item == ' '))
		return (NULL);
	else if (last)
		return (item);
	if (*item != ',')
		return (NULL);
	item++;
	if (ft_isdigit(*item) || *item == '-')
		return (item);
	return (NULL);
}

static int	set_coord(double *coord, char *item, char last)
{
	if (!item)
		return (print_error(ERROR, \
			"Invalid coordinate format. Expected: x,y,z"));
	if (str_to_double(item, coord, last))
		return (print_error(ERROR, \
			"The coordinate components must be a double"));
	return (SUCCESS);
}

int	parse_coord(t_point *coord, char *item)
{
	if (!item)
		return (print_error(ERROR, "A coordinate is missing"));
	if (set_coord(&coord->x, item, NO))
		return (ERROR);
	item = next_coord(item, NO);
	if (set_coord(&coord->y, item, NO))
		return (ERROR);
	item = next_coord(item, NO);
	if (set_coord(&coord->z, item, YES))
		return (ERROR);
	if (next_coord(item, YES))
		return (print_error(ERROR, "Too many coordinate components"));
	return (SUCCESS);
}
