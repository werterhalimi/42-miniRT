/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 13:15:10 by ncotte            #+#    #+#             */
/*   Updated: 2023/02/17 21:46:18 by shalimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static int	sub_parse_cylinder(t_cylinder *cy, t_list *current, t_object *obj)
{
	char	*item;

	item = next_item((char *)(current->content));
	if (parse_coord(&(cy->coord), item))
		return (ERROR);
	item = next_item(item);
	if (parse_vector(&(cy->direction), item, YES))
		return (ERROR);
	item = next_item(item);
	if (parse_length(&(cy->radius), item, "Diameter", YES))
		return (ERROR);
	item = next_item(item);
	if (parse_length(&(cy->semi_height), item, "Height", YES))
		return (ERROR);
	item = next_item(item);
	if (parse_color(&(cy->real_color), item))
		return (ERROR);
	item = next_item(item);
	if (item)
		return (parse_bonus(obj, item));
	return (SUCCESS);
}

int	parse_cylinder(t_scene *scene, t_list *current, t_object *object)
{
	t_cylinder	*cylinder;

	(void) scene;
	object->type = TYPE_CYLINDER;
	cylinder = ft_calloc(1, sizeof (t_cylinder));
	if (!cylinder)
		return (print_error(ERROR, "Cylinder allocation failed"));
	if (sub_parse_cylinder(cylinder, current, object))
		return (ERROR);
	cylinder->down = orthogonal_base(cylinder->direction, &cylinder->right);
	cylinder->ratio_color = update_color(cylinder->real_color, \
		1.0 - object->reflectance);
	object->object = cylinder;
	object->get_color = &get_color_cylinder;
	object->get_normal = &normal_cylinder;
	object->intersect = &intersect_cylinder;
	object->update = &update_cylinder;
	object->translation_relative = &translation_relative_cylinder;
	object->rotation_relative = &rotation_relative_cylinder;
	object->translation_absolute = &translation_absolute_cylinder;
	object->rotation_absolute = &rotation_absolute_cylinder;
	object->numpad_plus_minus = &height_cylinder;
	object->scroll = &radius_cylinder;
	return (SUCCESS);
}
