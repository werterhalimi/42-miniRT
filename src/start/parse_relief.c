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

int	parse_relief(void *ptr, char *item)
{
	if (!item)
		return (print_error(ERROR, "A relief is missing"));
	if (str_to_double(item, (double *)ptr, YES))
		return (print_error(ERROR, \
			"Invalid relief format. Required: one double"));
	if (*((double *)ptr) < 0.0)
		return (print_error(ERROR, \
			"The relief must be positive"));
	return (SUCCESS);
}
