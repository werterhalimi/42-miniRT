/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ratio.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 11:42:27 by ncotte            #+#    #+#             */
/*   Updated: 2023/01/30 11:42:29 by ncotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	parse_ratio(double *ratio, char *item)
{
	if (!item)
		return (print_error(ERROR, "A light ratio is missing"));
	if (str_to_double(item, ratio, YES))
		return (print_error(ERROR, \
			"Invalid light ratio format. Required: one double"));
	if (*ratio < 0.0 || 1.0 < *ratio)
		return (print_error(ERROR, \
			"The light ratio must be included in [0.0; 1.0]"));
	return (SUCCESS);
}
