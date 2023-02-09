/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_plane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 13:14:45 by ncotte            #+#    #+#             */
/*   Updated: 2023/02/09 13:14:51 by ncotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	parse_plane(t_scene *scene, t_list *current, t_objects *object)
{
	char	*item;
	t_plane	*plane;

	(void)scene;
	object->type = PLANE;
	plane = ft_calloc(1, sizeof (t_plane));
	if (!plane)
		return (print_error(ERROR, "Plane allocation failed"));
	item = next_item((char *)(current->content));
	if (parse_coord(&(plane->coord), item))
		return (ERROR);
	item = next_item(item);
	if (parse_vector(&(plane->normal), item, YES))
		return (ERROR);
	item = next_item(item);
	if (parse_color(&(plane->color), item))
		return (ERROR);
	if (next_item(item))
		return (print_error(ERROR, "Too many items for plane"));
	object->object = plane;
	object->get_color = &get_color_plane;
	object->intersect = &intersect_plane;
	object->update = &update_plane;
	return (SUCCESS);
}