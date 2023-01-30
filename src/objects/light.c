/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 19:27:01 by ncotte            #+#    #+#             */
/*   Updated: 2023/01/29 19:27:05 by ncotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	parse_light(t_scene *scene, t_list *current)
{
	char	*item;
	t_light	*light;

	light = scene->light;
	if (light)
		return (print_error(ERROR, \
			"There can be only one main light per scene"));
	light = ft_alloc(1, sizeof (t_light), NULL, ALLOC);
	if (!light)
		return (print_error(ERROR, "Main light allocation failed"));
	item = next_item((char *)(current->content));
	if (parse_coord(&(light->coord), item))
		return (ERROR);
	item = next_item(item);
	if (parse_ratio(&(light->ratio), item))
		return (ERROR);
	item = next_item(item);
	if (parse_color(&(light->color), item))
		return (ERROR);
	if (next_item(item))
		return (print_error(ERROR, "Too many items for main light"));
	scene->light = light;
	return (SUCCESS);
}
