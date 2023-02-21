/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spot_light.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 11:59:19 by ncotte            #+#    #+#             */
/*   Updated: 2023/02/16 11:59:21 by ncotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	ratio_spot_light(int key_code, t_scene *scene)
{
	t_spot_light	*spot_light;

	spot_light = (t_spot_light *)scene->objects[scene->index - 1]->object;
	if (key_code == NUMPAD_PLUS \
		&& spot_light->ratio <= 1.0 - LIGHT_RATIO_FACTOR + FLT_EPSILON)
		spot_light->ratio += LIGHT_RATIO_FACTOR;
	else if (key_code == NUMPAD_MINUS \
		&& spot_light->ratio >= LIGHT_RATIO_FACTOR - FLT_EPSILON)
		spot_light->ratio -= LIGHT_RATIO_FACTOR;
	update_scene(scene, SPOT_LIGHT_RATIO);
}

void	angle_spot_light(int mouse_code, t_scene *scene)
{
	t_spot_light	*spot_light;

	spot_light = (t_spot_light *)scene->objects[scene->index - 1]->object;
	if (mouse_code == SCROLL_UP && spot_light->angle < M_PI_2 - FOV_FACTOR)
		spot_light->angle += FOV_FACTOR;
	else if (mouse_code == SCROLL_DOWN && spot_light->angle > FOV_FACTOR)
		spot_light->angle -= FOV_FACTOR;
	update_scene(scene, SPOT_LIGHT_ANGLE);
}

void	update_spot_light(t_scene *scene, void *object, unsigned int flags)
{
	t_spot_light	*sl;

	if (!(flags & (CAMERA_TRANSLATION | SPOT_LIGHT_ALL)))
		return ;
	sl = (t_spot_light *)object;
	if (flags & LIGHT_RATIO)
		sl->ratio_color = update_color(sl->real_color, sl->ratio);
	if (flags & (SPOT_LIGHT_TRANSLATION | CAMERA_TRANSLATION))
		sl->relative_coord = sub_vectors(sl->coord, \
			scene->camera->coord);
	if (flags & SPOT_LIGHT_ANGLE)
		sl->cos_angle = -cos(sl->angle);
}
