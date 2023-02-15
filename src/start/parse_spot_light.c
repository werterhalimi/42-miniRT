/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_spot_light.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 12:00:44 by shalimi           #+#    #+#             */
/*   Updated: 2023/02/15 12:48:11 by shalimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

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
	if (parse_color(&(light->color), item))
		return (ERROR);
	if (next_item(item))
		return (print_error(ERROR, "Too many items for spot light"));
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
	*spot = (ft_lstnew(light));
	return (SUCCESS);
}
