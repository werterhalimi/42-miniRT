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

static int	sub_parse_spot_light(t_spot_light *spot_light, t_list *current)
{
	char	*item;

	item = next_item((char *)(current->content));
	if (parse_coord(&(spot_light->coord), item))
		return (ERROR);
	item = next_item(item);
	if (parse_vector(&(spot_light->direction), item, YES))
		return (ERROR);
	item = next_item(item);
	if (parse_ratio(&(spot_light->ratio), item))
		return (ERROR);
	item = next_item(item);
	if (parse_angle(&(spot_light->angle), item))
		return (ERROR);
	item = next_item(item);
	if (parse_color(&(spot_light->color), item))
		return (ERROR);
	if (next_item(item))
		return (print_error(ERROR, "Too many items for spot spot_light"));
	spot_light->down = orthogonal_base(spot_light->direction, \
		&spot_light->right);
	return (SUCCESS);
}

int	parse_spot_light(t_scene *scene, t_list *current, t_object *object)
{
	t_spot_light	*spot_light;
	t_list			*light;

	spot_light = ft_calloc(1, sizeof (t_spot_light));
	if (!spot_light)
		return (print_error(ERROR, "Spot light allocation failed"));
	if (sub_parse_spot_light(spot_light, current))
		return (ERROR);
	light = ft_lstnew(spot_light);
	if (!light)
		return (ERROR);
	ft_lstadd_front(&scene->spot_lights, light);
	object->object = spot_light;
	object->print = &print_spot_light;
	object->get_color = &get_color_spot_light;
	object->intersect = &intersect_spot_light;
	object->update = &update_spot_light;
	object->translation_relative = &translation_relative_spot_light;
	object->rotation_relative = &rotation_relative_spot_light;
	object->translation_absolute = &translation_absolute_spot_light;
	object->rotation_absolute = &rotation_absolute_spot_light;
	object->numpad_plus_minus = &ratio_spot_light;
	object->scroll = &angle_spot_light;
	object->type = SPOT_LIGHT;
	return (SUCCESS);
}
