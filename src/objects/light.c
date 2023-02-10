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

void	update_light(t_scene *scene, void *object, unsigned int flags)
{
	t_light	*light;

	if (!(flags & (CAMERA_TRANSLATION | LIGHT_TRANSLATION)))
		return ;
	light = (t_light *)object;
	light->relative_coord = sub_vectors(light->coord, scene->camera->coord);
}

double	intersect_light(t_point ray, void *object)
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

void	translation_absolute_light(t_scene *scene, t_point vector)
{
	scene->light->coord = add_vectors(scene->light->coord, vector);
	update_scene(scene, LIGHT_TRANSLATION);
}

unsigned int	get_color_light(t_scene *scene, void *object)
{
	t_light	*light;

	(void)scene;
	light = (t_light *)object;
	return (color_trgb(light->color));
}
