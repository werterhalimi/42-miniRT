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

static void	update_fov(t_scene *scene)
{
	scene->camera->size_x = tan(scene->camera->fov * 0.5);
	scene->camera->pixel_size = 2.0 * scene->camera->size_x \
		/ (double)(scene->width);
	scene->camera->size_y = scene->camera->size_x * (double)(scene->height) \
		/ (double)(scene->width);
}

void	update_camera(t_scene *scene, char mode)
{
	t_camera	*camera;
	t_point		tmp;

	camera = scene->camera;
	if (mode == ROTATION_YAW)
		camera->right = cross_product(camera->down, camera->front);
	if (mode == ROTATION_PITCH || mode == ROTATION_ROLL || mode == ALL)
		camera->down = cross_product(camera->front, camera->right);
	if (mode == FOV || mode == ALL)
		update_fov(scene);
	if (mode != TRANSLATION)
	{
		camera->shift_x = scalar_multi(camera->pixel_size, camera->right);
		camera->shift_y = scalar_multi(camera->pixel_size, camera->down);
	}
	tmp = add_vectors(scalar_multi(camera->size_x, camera->right), \
		scalar_multi(camera->size_y, camera->down));
	scene->window_corner = sub_vectors(add_vectors(camera->coord, \
		camera->front), tmp);
}
