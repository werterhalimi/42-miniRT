/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 13:15:00 by ncotte            #+#    #+#             */
/*   Updated: 2023/02/17 21:45:36 by shalimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static int	sub_parse_sphere(t_sphere *sphere, t_list *current, t_object *obj)
{
	char	*item;

	item = next_item((char *)(current->content));
	if (parse_coord(&(sphere->coord), item))
		return (ERROR);
	item = next_item(item);
	if (parse_length(&(sphere->radius), item, "Diameter", YES))
		return (ERROR);
	item = next_item(item);
	if (parse_color(&(sphere->color), item))
		return (ERROR);
	item = next_item(item);
	if (item)
		return (parse_bonus(obj, item));
	return (SUCCESS);
}

int	parse_sphere(t_scene *scene, t_list *current, t_object *object)
{
	t_sphere	*sphere;

	(void) scene;
	object->type = TYPE_SPHERE;
	sphere = ft_calloc(1, sizeof (t_sphere));
	if (!sphere)
		return (print_error(ERROR, "Sphere allocation failed"));
	if (sub_parse_sphere(sphere, current, object))
		return (ERROR);
	sphere->front = new_point(0.0, 0.0, 1.0);
	sphere->down = orthogonal_base(sphere->front, &sphere->right);
	object->object = sphere;
	object->get_color = &get_color_sphere;
	object->get_normal = &normal_sphere;
	object->intersect = &intersect_sphere;
	object->update = &update_sphere;
	object->translation_absolute = &translation_absolute_sphere;
	object->scroll = &radius_sphere;
	return (SUCCESS);
}
