/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_spot_light.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 12:00:44 by shalimi           #+#    #+#             */
/*   Updated: 2023/02/16 03:38:45 by shalimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static int	parse_angle(double *angle, char *item)
{
	if (!item)
		return (print_error(ERROR, "A CAMERA_FOV is missing"));
	if (str_to_double(item, angle, YES))
		return (print_error(ERROR, \
			"Invalid CAMERA_FOV format. Required: one double"));
	if (*angle < 0.0 || 180.0 < *angle)
		return (print_error(ERROR, \
			"The CAMERA_FOV must be included in [0.0; 180.0]"));
	*angle = *angle * M_PI / 180.0;
	*angle /= 2;
	return (SUCCESS);
}

static int	sub_parse_spot_light(t_spot_light *light, t_list *current)
{
	char	*item;

	item = next_item((char *)(current->content));
	if (parse_coord(&(light->coord), item))
		return (ERROR);
	item = next_item(item);
	if (parse_coord(&(light->direction), item))
		return (ERROR);
	item = next_item(item);
	if (parse_ratio(&(light->ratio), item))
		return (ERROR);
	item = next_item(item);
	if (parse_angle(&(light->angle), item))
		return (ERROR);
	item = next_item(item);
	if (parse_color(&(light->color), item))
		return (ERROR);
	if (next_item(item))
		return (print_error(ERROR, "Too many items for spot light"));
	light->angle /= 2;
	return (SUCCESS);
}


int	parse_spot_light(t_list *current, t_list **spot)
{
	t_spot_light	*light;

	light = ft_calloc(1, sizeof (t_spot_light));
	if (!light)
		return (print_error(ERROR, "Spot light allocation failed"));
	if (sub_parse_spot_light(light, current))
		return (ERROR);
	light->direction = unit_vector(light->direction);
	*spot = (ft_lstnew(light));
	return (SUCCESS);
}
