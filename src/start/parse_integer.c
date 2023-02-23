/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_integer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 21:12:54 by shalimi           #+#    #+#             */
/*   Updated: 2023/02/17 21:51:54 by shalimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	parse_integer(void *ptr, char *item)
{
	int		number;
	char	*buff;

	if (!item)
		return (print_error(ERROR, "A number is missing"));
	number = ft_atoi(item);
	buff = ft_itoa(number);
	if (ft_strncmp(item, buff, ft_strlen(buff)) || number < 0)
		return (print_error(ERROR, \
			"Invalid format. Required: one positive integer"));
	*(int *)ptr = number;
	return (SUCCESS);
}
