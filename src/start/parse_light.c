/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 13:15:27 by ncotte            #+#    #+#             */
/*   Updated: 2023/02/17 21:04:54 by shalimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static int	sub_parse_light(t_light *light, t_list *current)
{
	char	*item;

	item = next_item((char *)(current->content));
	if (parse_coord(&(light->coord), item))
		return (ERROR);
	item = next_item(item);
	if (parse_ratio(&(light->ratio), item))
		return (ERROR);
	item = next_item(item);
	if (parse_color(&(light->real_color), item))
		return (ERROR);
	if (next_item(item))
		return (print_error(ERROR, "Too many items for main light"));
	return (SUCCESS);
}

int	parse_light(t_scene *scene, t_list *current, t_object *object)
{
	t_light	*light;

	light = scene->light;
	if (light)
		return (print_error(ERROR, \
			"There can be only one main light per scene"));
	light = ft_calloc(1, sizeof (t_light));
	if (!light)
		return (print_error(ERROR, "Main light allocation failed"));
	if (sub_parse_light(light, current))
		return (ERROR);
	scene->light = light;
	object->object = light;
	object->get_color = &get_color_light;
	object->intersect = &intersect_light;
	object->update = &update_light;
	object->translation_absolute = &translation_absolute_light;
	object->numpad_plus_minus = &ratio_main_light;
	object->type = TYPE_MAIN_LIGHT;
	return (SUCCESS);
}
