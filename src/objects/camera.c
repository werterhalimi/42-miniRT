/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 19:27:20 by ncotte            #+#    #+#             */
/*   Updated: 2023/01/29 19:27:22 by ncotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	update_camera(t_scene *scene, unsigned int flags)
{
	t_camera		*camera;
	static t_point	tmp;

	if (!(flags & CAMERA_ALL))
		return ;
	camera = scene->camera;
	if (flags & CAMERA_FOV)
	{
		scene->camera->size_x = tan(scene->camera->fov * 0.5);
		scene->camera->pixel_size = 2.0 * scene->camera->size_x \
		/ (double)(scene->width);
		scene->camera->size_y = scene->camera->size_x * (double)(scene->height) \
		/ (double)(scene->width);
	}
	if (flags == UPDATE_ALL || flags & (CAMERA_ROTATION | CAMERA_FOV))
	{
		camera->shift_x = scalar_multi(camera->pixel_size, camera->right);
		camera->shift_y = scalar_multi(camera->pixel_size, camera->down);
		tmp = sub_vectors(camera->front, add_vectors(scalar_multi(camera->size_x, \
			camera->right), scalar_multi(camera->size_y, camera->down)));
	}
	scene->window_corner = add_vectors(camera->coord, tmp);
}
