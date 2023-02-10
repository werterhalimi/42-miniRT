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

void	translation_relative_camera(int key_code, t_scene *scene)
{
	t_point	vector;

	vector = new_point(0.0, 0.0, 0.0);
	if (key_code == KEY_W)
		vector = scalar_multi(TRANSLATION_FACTOR, scene->camera->front);
	else if (key_code == KEY_S)
		vector = scalar_multi(-TRANSLATION_FACTOR, scene->camera->front);
	else if (key_code == KEY_A)
		vector = scalar_multi(-TRANSLATION_FACTOR, scene->camera->right);
	else if (key_code == KEY_D)
		vector = scalar_multi(TRANSLATION_FACTOR, scene->camera->right);
	else if (key_code == KEY_E)
		vector = scalar_multi(-TRANSLATION_FACTOR, scene->camera->down);
	else if (key_code == KEY_Q)
		vector = scalar_multi(TRANSLATION_FACTOR, scene->camera->down);
	scene->camera->coord = add_vectors(scene->camera->coord, vector);
	update_scene(scene, CAMERA_TRANSLATION);
}

void	rotation_relative_camera(int key_code, t_scene *scene)
{
	if (key_code == NUMPAD_2)
		scene->camera->front = unit_vector(sub_vectors(scene->camera->front, \
			scalar_multi(ROTATION_FACTOR, scene->camera->down)));
	else if (key_code == NUMPAD_8)
		scene->camera->front = unit_vector(add_vectors(scene->camera->front, \
			scalar_multi(ROTATION_FACTOR, scene->camera->down)));
	if (key_code == NUMPAD_2 || key_code == NUMPAD_8)
		update_scene(scene, CAMERA_PITCH);
	if (key_code == NUMPAD_4)
		scene->camera->front = unit_vector(sub_vectors(scene->camera->front, \
			scalar_multi(ROTATION_FACTOR, scene->camera->right)));
	else if (key_code == NUMPAD_6)
		scene->camera->front = unit_vector(add_vectors(scene->camera->front, \
			scalar_multi(ROTATION_FACTOR, scene->camera->right)));
	if (key_code == NUMPAD_4 || key_code == NUMPAD_6)
		update_scene(scene, CAMERA_YAW);
	if (key_code == NUMPAD_7)
		scene->camera->right = unit_vector(sub_vectors(scene->camera->right, \
			scalar_multi(ROTATION_FACTOR, scene->camera->down)));
	else if (key_code == NUMPAD_9)
		scene->camera->right = unit_vector(add_vectors(scene->camera->right, \
			scalar_multi(ROTATION_FACTOR, scene->camera->down)));
	if (key_code == NUMPAD_7 || key_code == NUMPAD_9)
		update_scene(scene, CAMERA_ROLL);
}

void	translation_absolute_camera(t_scene *scene, t_point vector)
{
	scene->camera->coord = add_vectors(scene->camera->coord, vector);
	update_scene(scene, CAMERA_TRANSLATION);
}

void	rotation_absolute_camera(t_scene *scene, t_matrix matrix)
{
	scene->camera->front = matrix_vector_multi(matrix, scene->camera->front);
	scene->camera->down = matrix_vector_multi(matrix, scene->camera->down);
	update_scene(scene, CAMERA_YAW);
}

void	update_camera(t_scene *scene, unsigned int flags)
{
	t_camera	*camera;
	t_point		tmp;

	if (!(flags & CAMERA_ALL))
		return ;
	camera = scene->camera;
	if (flags & CAMERA_YAW && !(flags & (CAMERA_PITCH | CAMERA_ROLL)))
		camera->right = cross_product(camera->down, camera->front);
	else if (flags == UPDATE_ALL || (flags & (CAMERA_PITCH | CAMERA_ROLL) \
		&& !(flags & CAMERA_YAW)))
		camera->down = cross_product(camera->front, camera->right);
	if (flags & CAMERA_FOV)
		update_fov(scene);
	if (flags == UPDATE_ALL || !(flags & CAMERA_TRANSLATION))
	{
		camera->shift_x = scalar_multi(camera->pixel_size, camera->right);
		camera->shift_y = scalar_multi(camera->pixel_size, camera->down);
	}
	tmp = add_vectors(scalar_multi(camera->size_x, camera->right), \
		scalar_multi(camera->size_y, camera->down));
	scene->window_corner = sub_vectors(add_vectors(camera->coord, \
		camera->front), tmp);
}
