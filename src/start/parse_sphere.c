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

static int	bonus_parse_sphere(t_sphere *sphere, char *item)
{
	sphere->color_bis = ft_calloc(1, sizeof (*sphere->color_bis));
	if (!sphere->color_bis || parse_color(sphere->color_bis, item))
		return (ERROR);
	if (next_item(item))
		return (print_error(ERROR, "Too many items for sphere"));
	return (SUCCESS);
}

static int	sub_parse_sphere(t_sphere *sphere, t_list *current)
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
		return (bonus_parse_sphere(sphere, item));
	return (SUCCESS);
}

int	parse_sphere(t_scene *scene, t_list *current, t_object *object)
{
	t_sphere	*sphere;

	(void) scene;
	object->type = SPHERE;
	sphere = ft_calloc(1, sizeof (t_sphere));
	if (!sphere)
		return (print_error(ERROR, "Sphere allocation failed"));
	if (sub_parse_sphere(sphere, current))
		return (ERROR);
	object->object = sphere;
	object->print = &print_sphere;
	object->get_color = &get_color_sphere;
	object->get_normal = &normal_sphere;
	object->intersect = &intersect_sphere;
	object->update = &update_sphere;
	object->translation_absolute = &translation_absolute_sphere;
	object->scroll = &radius_sphere;
	return (SUCCESS);
}
