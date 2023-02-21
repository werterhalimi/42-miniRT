/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 10:44:19 by ncotte            #+#    #+#             */
/*   Updated: 2023/02/10 10:44:21 by ncotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_color	update_color(t_color real_color, double ratio)
{
	t_color	ratio_color;

	ratio_color.r = real_color.r * ratio;
	ratio_color.g = real_color.g * ratio;
	ratio_color.b = real_color.b * ratio;
	return (ratio_color);
}

void	update_scene(t_scene *scene, unsigned int flags)
{
	int	i;

	update_camera(scene, flags);
	update_amb_light(scene, flags);
	i = -1;
	if (flags & CAMERA_TRANSLATION)
		while (scene->objects[++i])
			scene->objects[i]->update(scene, scene->objects[i]->object, flags);
	else if (scene->index)
		scene->objects[scene->index - 1]->update(scene, \
			scene->objects[scene->index - 1]->object, flags);
}
