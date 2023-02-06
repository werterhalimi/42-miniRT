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

int	is_plane(t_point point, t_plane plane)
{
	if (dot_product(sub_vectors(point, plane.coord), plane.normal))
		return (NO);
	return (YES);
}

static void	update_plane(t_scene *scene, void *object)
{
	t_plane	*plane;

	plane = (t_plane *)object;
	plane->value = dot_product(sub_vectors(plane->coord, \
		scene->camera->coord), plane->normal);
}

static double	intersect_plane(t_point ray, void *object)
{
	t_plane	*plane;
	double	div;
	double	t;

	plane = (t_plane *)object;
	div = dot_product(ray, plane->normal);
	if (!div)
		return (INFINITY);
	t = plane->value / div;
	if (t < 0.0)
		return (INFINITY);
	return (t);
}

static unsigned int	get_color_plane(t_scene *scene, void *object)
{
	t_plane	*plane;

	(void)scene;
	plane = (t_plane *)object;
	return (color_trgb(plane->color));
}

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
