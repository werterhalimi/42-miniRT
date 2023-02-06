/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 19:27:01 by ncotte            #+#    #+#             */
/*   Updated: 2023/01/29 19:27:05 by ncotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	update_light(t_scene *scene, void *object)
{
	t_light	*light;

	light = (t_light *)object;
	light->relative_coord = sub_vectors(light->coord, scene->camera->coord);
}

static double	intersect_light(t_point ray, void *object)
{
	t_light	*light;
	double	t;

	light = (t_light *)object;
	t = light->relative_coord.x / ray.x;
	if (is_null(add_vectors(scalar_multi(t, ray), \
		light->relative_coord)) && t >= 0.0)
		return (t);
	return (INFINITY);
}

static unsigned int	get_color_light(t_scene *scene, void *object)
{
	t_light	*light;

	(void)scene;
	light = (t_light *)object;
	return (color_trgb(light->color));
}

int	parse_light(t_scene *scene, t_list *current, t_objects *object)
{
	char	*item;
	t_light	*light;

	light = scene->light;
	if (light)
		return (print_error(ERROR, \
			"There can be only one main light per scene"));
	light = ft_calloc(1, sizeof (t_light));
	if (!light)
		return (print_error(ERROR, "Main light allocation failed"));
	item = next_item((char *)(current->content));
	if (parse_coord(&(light->coord), item))
		return (ERROR);
	item = next_item(item);
	if (parse_ratio(&(light->ratio), item))
		return (ERROR);
	item = next_item(item);
	if (parse_color(&(light->color), item))
		return (ERROR);
	if (next_item(item))
		return (print_error(ERROR, "Too many items for main light"));
	scene->light = light;
	object->object = light;
	object->get_color = &get_color_light;
	object->intersect = &intersect_light;
	object->update = &update_light;
	object->type = MAIN_LIGHT;
	return (SUCCESS);
}
