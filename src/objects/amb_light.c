/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   amb_light.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 19:27:30 by ncotte            #+#    #+#             */
/*   Updated: 2023/01/29 19:27:32 by ncotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	ratio_amb_light(int key_code, t_scene *scene)
{
	if (key_code == NUMPAD_PLUS \
		&& scene->amb_light->ratio <= 1.0 - LIGHT_RATIO_FACTOR + FLT_EPSILON)
		scene->amb_light->ratio += LIGHT_RATIO_FACTOR;
	else if (key_code == NUMPAD_MINUS \
		&& scene->amb_light->ratio >= LIGHT_RATIO_FACTOR - FLT_EPSILON)
		scene->amb_light->ratio -= LIGHT_RATIO_FACTOR;
	update_scene(scene, AMB_LIGHT_RATIO);
}

void	update_amb_light(t_scene *scene, unsigned int flags)
{
	t_amb_light	*al;

	if (!(flags & AMB_LIGHT_RATIO))
		return ;
	al = scene->amb_light;
	al->ratio_color = update_color(al->real_color, al->ratio);
}
