/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 19:27:01 by ncotte            #+#    #+#             */
/*   Updated: 2023/02/16 01:34:21 by shalimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	ratio_main_light(int key_code, t_scene *scene)
{
	if (key_code == NUMPAD_PLUS \
		&& scene->light->ratio <= 1.0 - LIGHT_RATIO_FACTOR + FLT_EPSILON)
		scene->light->ratio += LIGHT_RATIO_FACTOR;
	else if (key_code == NUMPAD_MINUS \
		&& scene->light->ratio >= LIGHT_RATIO_FACTOR - FLT_EPSILON)
		scene->light->ratio -= LIGHT_RATIO_FACTOR;
}

void	update_light(t_scene *scene, void *object, unsigned int flags)
{
	t_light	*light;

	if (!(flags & (CAMERA_TRANSLATION | LIGHT_TRANSLATION)))
		return ;
	light = (t_light *)object;
	light->relative_coord = sub_vectors(light->coord, scene->camera->coord);
}
