/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 19:28:07 by ncotte            #+#    #+#             */
/*   Updated: 2023/01/29 19:28:08 by ncotte           ###   ########.fr       */
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
	if (parse_vector(&(cylinder->vector), item))
		return (ERROR);
	item = next_item(item);
	if (parse_length(&(cylinder->diameter), item, "Diameter"))
		return (ERROR);
	item = next_item(item);
	if (parse_length(&(cylinder->height), item, "Height"))
		return (ERROR);
	item = next_item(item);
	if (parse_color(&(cylinder->color), item))
		return (ERROR);
	if (next_item(item))
		return (print_error(ERROR, "Too many items for cylinder"));
	return (SUCCESS);
}

int	parse_cylinder(t_scene *scene, t_list *current)
{
	int			i;
	t_cylinder	*cylinder;

	i = 0;
	while (!((scene->objects)[i]))
		i++;
	cylinder = malloc(sizeof (t_cylinder));
	if (!cylinder)
		return (print_error(ERROR, "Cylinder allocation failed"));
	if (sub_parse_cylinder(cylinder, current))
		return (ERROR);
	(scene->objects)[i] = cylinder;
	return (SUCCESS);
}
