/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 19:27:46 by ncotte            #+#    #+#             */
/*   Updated: 2023/01/29 19:27:48 by ncotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	parse_plane(t_scene *scene, t_list *current)
{
	int		i;
	char	*item;
	t_plane	*plane;

	i = 0;
	while ((scene->objects)[i])
		i++;
	plane = ft_calloc(1, sizeof (t_plane));
	if (!plane)
		return (print_error(ERROR, "Plane allocation failed"));
	item = next_item((char *)(current->content));
	if (parse_coord(&(plane->coord), item))
		return (ERROR);
	item = next_item(item);
	if (parse_vector(&(plane->vector), item))
		return (ERROR);
	item = next_item(item);
	if (parse_color(&(plane->color), item))
		return (ERROR);
	if (next_item(item))
		return (print_error(ERROR, "Too many items for plane"));
	(scene->objects)[i] = plane;
	return (SUCCESS);
}
