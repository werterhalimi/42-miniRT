/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_angle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 10:18:59 by ncotte            #+#    #+#             */
/*   Updated: 2023/02/16 10:19:01 by ncotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	parse_angle(double *angle, char *item)
{
	if (!item)
		return (print_error(ERROR, "An angle is missing"));
	if (str_to_double(item, angle, YES))
		return (print_error(ERROR, \
			"Invalid angle format. Required: one double"));
	if (*angle < 0.0 || 180.0 < *angle)
		return (print_error(ERROR, \
			"The angle must be included in [0.0; 180.0]"));
	*angle *= PI_360;
	return (SUCCESS);
}
