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

void	fov_camera(int mouse_code, t_scene *scene)
{
	if (mouse_code == SCROLL_UP && scene->camera->fov < M_PI - FOV_FACTOR)
		scene->camera->fov += FOV_FACTOR;
	else if (mouse_code == SCROLL_DOWN && scene->camera->fov > FOV_FACTOR)
		scene->camera->fov -= FOV_FACTOR;
	update_scene(scene, CAMERA_FOV);
}

void	update_camera(t_scene *scene, unsigned int flags)
{
	t_camera		*cam;
	static t_point	tmp;

	if (!(flags & CAMERA_ALL))
		return ;
	cam = scene->camera;
	if (flags & CAMERA_FOV)
	{
		scene->camera->size_x = tan(scene->camera->fov * 0.5);
		scene->camera->pixel_size = 2.0 * scene->camera->size_x \
		/ (double)(scene->width);
		scene->camera->size_y = scene->camera->size_x * (double)(scene->height) \
		/ (double)(scene->width);
	}
	if (flags & (CAMERA_ROTATION | CAMERA_FOV))
	{
		cam->shift_x = scalar_multi(cam->pixel_size, cam->right);
		cam->shift_y = scalar_multi(cam->pixel_size, cam->down);
		tmp = sub_vectors(cam->front, add_vectors(scalar_multi(cam->size_x, \
			cam->right), scalar_multi(cam->size_y, cam->down)));
	}
	scene->window_corner = add_vectors(cam->coord, tmp);
}
