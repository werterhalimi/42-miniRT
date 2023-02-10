/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 13:15:10 by ncotte            #+#    #+#             */
/*   Updated: 2023/02/09 13:15:12 by ncotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static int	sub_parse_cylinder(t_cylinder *cylinder, t_list *current)
{
	char	*item;

	item = next_item((char *)(current->content));
	if (parse_coord(&(cylinder->coord), item))
		return (ERROR);
	item = next_item(item);
	if (parse_vector(&(cylinder->direction), item, YES))
		return (ERROR);
	item = next_item(item);
	if (parse_length(&(cylinder->radius), item, "Diameter", YES))
		return (ERROR);
	item = next_item(item);
	if (parse_length(&(cylinder->semi_height), item, "Height", YES))
		return (ERROR);
	item = next_item(item);
	if (parse_color(&(cylinder->color), item))
		return (ERROR);
	if (next_item(item))
		return (print_error(ERROR, "Too many items for cylinder"));
	return (SUCCESS);
}

int	parse_cylinder(t_scene *scene, t_list *current, t_objects *object)
{
	t_cylinder	*cylinder;

	(void)scene;
	object->type = CYLINDER;
	cylinder = ft_calloc(1, sizeof (t_cylinder));
	if (!cylinder)
		return (print_error(ERROR, "Cylinder allocation failed"));
	if (sub_parse_cylinder(cylinder, current))
		return (ERROR);
	object->object = cylinder;
	object->get_color = &get_color_cylinder;
	object->intersect = &intersect_cylinder;
	object->update = &update_cylinder;
	object->translation_relative = &translation_relative_cylinder;
	object->rotation_relative = &rotation_relative_cylinder;
	object->translation_absolute = &translation_absolute_cylinder;
	object->rotation_absolute = &rotation_absolute_cylinder;
	return (SUCCESS);
}
