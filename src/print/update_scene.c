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

void	update_scene(t_scene *scene, unsigned int flags)
{
	int	i;

	update_camera(scene, flags);
	i = -1;
	if (flags & CAMERA_TRANSLATION)
		while (scene->objects[++i])
			scene->objects[i]->update(scene, scene->objects[i]->object, flags);
	else if (scene->index)
		scene->objects[scene->index - 1]->update(scene, \
			scene->objects[scene->index - 1]->object, flags);
}