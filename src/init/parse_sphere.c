/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 13:15:00 by ncotte            #+#    #+#             */
/*   Updated: 2023/02/12 21:07:18 by shalimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	parse_sphere(t_scene *scene, t_list *current, t_objects *object)
{
	char		*item;
	t_sphere	*sphere;

	(void)scene;
	object->type = SPHERE;
	sphere = ft_calloc(1, sizeof (t_sphere));
	if (!sphere)
		return (print_error(ERROR, "Sphere allocation failed"));
	item = next_item((char *)(current->content));
	if (parse_coord(&(sphere->coord), item))
		return (ERROR);
	item = next_item(item);
	if (parse_length(&(sphere->radius), item, "Diameter", YES))
		return (ERROR);
	item = next_item(item);
	if (parse_color(&(sphere->color), item))
		return (ERROR);
	if (next_item(item))
		return (print_error(ERROR, "Too many items for sphere"));
	object->object = sphere;
	object->get_color = &get_color_sphere;
	object->intersect = &intersect_sphere;
	object->intersect_absolute = &intersect_sphere_absolute;
	object->update = &update_sphere;
	object->translation_absolute = &translation_absolute_sphere;
	return (SUCCESS);
}
