/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translation_spot_light.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 12:09:47 by ncotte            #+#    #+#             */
/*   Updated: 2023/02/16 12:09:49 by ncotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	translation_relative_spot_light(int key_code, t_scene *scene)
{
	t_point			vector;
	t_spot_light	*spot_light;

	spot_light = (t_spot_light *)scene->objects[scene->index - 1]->object;
	if (key_code == KEY_W)
		vector = scalar_multi(TRANSLATION_FACTOR, spot_light->direction);
	else if (key_code == KEY_S)
		vector = scalar_multi(-TRANSLATION_FACTOR, spot_light->direction);
	else
		return ;
	spot_light->coord = add_vectors(spot_light->coord, vector);
	update_scene(scene, SPOT_LIGHT_TRANSLATION);
}

void	translation_absolute_spot_light(t_scene *scene, t_point vector)
{
	t_spot_light	*spot_light;

	spot_light = (t_spot_light *)scene->objects[scene->index - 1]->object;
	spot_light->coord = add_vectors(spot_light->coord, vector);
	update_scene(scene, SPOT_LIGHT_TRANSLATION);
}
