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

int	parse_specular(t_object *object, char *item)
{
	char	*buff;

	if (!item)
		return (print_error(ERROR, "A specular is missing"));
	object->specular = ft_atoi(item);
	buff = ft_itoa(object->specular);
	if (ft_strncmp(item, buff, ft_strlen(buff)) || object->specular < 0)
		return (print_error(ERROR, \
			"Invalid specular format. Required: one positive int"));
	return (SUCCESS);
}
