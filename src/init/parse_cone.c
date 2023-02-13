/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cone.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 16:32:15 by ncotte            #+#    #+#             */
/*   Updated: 2023/02/13 16:32:18 by ncotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static int	sub_parse_cone(t_cone *cone, t_list *current)
{
	char	*item;

	item = next_item((char *)(current->content));
	if (parse_coord(&(cone->coord), item))
		return (ERROR);
	item = next_item(item);
	if (parse_vector(&(cone->direction), item, YES))
		return (ERROR);
	item = next_item(item);
	if (parse_length(&(cone->radius), item, "Diameter", YES))
		return (ERROR);
	item = next_item(item);
	if (parse_length(&(cone->height), item, "Height", NO))
		return (ERROR);
	item = next_item(item);
	if (parse_color(&(cone->color), item))
		return (ERROR);
	if (next_item(item))
		return (print_error(ERROR, "Too many items for cone"));
	return (SUCCESS);
}

int	parse_cone(t_scene *scene, t_list *current, t_objects *object)
{
	t_cone	*cone;

	(void)scene;
	object->type = CONE;
	cone = ft_calloc(1, sizeof (t_cone));
	if (!cone)
		return (print_error(ERROR, "Cylinder allocation failed"));
	if (sub_parse_cone(cone, current))
		return (ERROR);
	cone->down = orthogonal_base(cone->direction, &cone->right);
	object->object = cone;
	object->get_color = &get_color_cone;
	object->intersect = &intersect_cone;
	object->update = &update_cone;
	object->translation_relative = &translation_relative_cone;
	object->rotation_relative = &rotation_relative_cone;
	object->translation_absolute = &translation_absolute_cone;
	object->rotation_absolute = &rotation_absolute_cone;
	return (SUCCESS);
}
