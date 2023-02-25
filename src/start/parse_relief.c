/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_relief.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 19:23:40 by shalimi           #+#    #+#             */
/*   Updated: 2023/02/25 19:48:05 by shalimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	parse_relief(void *relief, char *item)
{
	if (!item)
		return (print_error(ERROR, "An relief is missing"));
	if (str_to_double(item, relief, YES))
		return (print_error(ERROR, \
			"Invalid relief format. Required: one double"));
	if (*((double *)relief) < 0.0)
		return (print_error(ERROR, \
			"The relief must be {> 0}"));
	return (SUCCESS);
}
