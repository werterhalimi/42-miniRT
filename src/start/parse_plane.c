/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_plane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 13:14:45 by ncotte            #+#    #+#             */
/*   Updated: 2023/02/17 21:04:54 by shalimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static int	bonus_parse_plane(t_plane *plane, char *item)
{
	plane->color_bis = ft_calloc(1, sizeof (*plane->color_bis));
	if (!plane->color_bis || parse_color(plane->color_bis, item))
		return (ERROR);
	if (next_item(item))
		return (print_error(ERROR, "Too many items for plane"));
	return (SUCCESS);
}

static int	sub_parse_plane(t_plane *plane, t_list *current)
{
	char	*item;

	item = next_item((char *)(current->content));
	if (parse_coord(&(plane->coord), item))
		return (ERROR);
	item = next_item(item);
	if (parse_vector(&(plane->normal), item, YES))
		return (ERROR);
	item = next_item(item);
	if (parse_color(&(plane->color), item))
		return (ERROR);
	item = next_item(item);
	if (item)
		return (bonus_parse_plane(plane, item));
	return (SUCCESS);
}

int	parse_plane(t_scene *scene, t_list *current, t_object *object)
{
	t_plane	*plane;

	(void) scene;
	object->type = PLANE;
	plane = ft_calloc(1, sizeof (t_plane));
	if (!plane)
		return (print_error(ERROR, "Plane allocation failed"));
	if (sub_parse_plane(plane, current))
		return (ERROR);
	plane->down = orthogonal_base(plane->normal, &plane->right);
	object->object = plane;
	object->get_color = &get_color_plane;
	object->get_normal = &normal_plane;
	object->intersect = &intersect_plane;
	object->update = &update_plane;
	object->translation_relative = &translation_relative_plane;
	object->rotation_relative = &rotation_relative_plane;
	object->translation_absolute = &translation_absolute_plane;
	object->rotation_absolute = &rotation_absolute_plane;
	return (SUCCESS);
}
