/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_amb_light.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 13:15:45 by ncotte            #+#    #+#             */
/*   Updated: 2023/02/09 13:15:46 by ncotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	parse_amb_light(t_scene *scene, t_list *current, t_object *object)
{
	char		*item;
	t_amb_light	*amb_light;

	(void) object;
	amb_light = scene->amb_light;
	if (amb_light)
		return (print_error(ERROR, \
			"There can be only one ambient light per scene"));
	amb_light = ft_calloc(1, sizeof (t_amb_light));
	if (!amb_light)
		return (print_error(ERROR, "Ambient light allocation failed"));
	item = next_item((char *)(current->content));
	if (parse_ratio(&(amb_light->ratio), item))
		return (ERROR);
	item = next_item(item);
	if (parse_color(&(amb_light->color), item))
		return (ERROR);
	if (next_item(item))
		return (print_error(ERROR, "Too many items for ambient light"));
	scene->amb_light = amb_light;
	return (SUCCESS);
}
