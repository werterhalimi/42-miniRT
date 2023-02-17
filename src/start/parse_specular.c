/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_specular.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 21:12:54 by shalimi           #+#    #+#             */
/*   Updated: 2023/02/17 21:51:54 by shalimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	parse_specular(int *specular, char *item)
{
	char	*buff;
	if (!item)
		return (print_error(ERROR, "A specular is missing"));
	*specular = atoi(item);
	buff = ft_itoa(*specular);
	if (ft_strncmp(item, buff, ft_strlen(buff)))
		return (print_error(ERROR, \
			"Invalid angle format. Required: one int"));
	return (SUCCESS);
}
