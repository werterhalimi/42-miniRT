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

void	translation_relative_camera(int key_code, t_scene *scene)
{
	t_point	vector;

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
	else
		vector = scalar_multi(TRANSLATION_FACTOR, scene->camera->down);
	scene->camera->coord = add_vectors(scene->camera->coord, vector);
	update_scene(scene, CAMERA_TRANSLATION);
}

void	rotation_relative_camera(int key_code, t_scene *scene)
{
	t_camera *camera;

	camera = scene->camera;
	if (key_code == NUMPAD_2)
		camera->down = matrix_vector_multi(matrix_rotation_relative(camera->right, \
			sin_rot()), camera->down);
	else if (key_code == NUMPAD_8)
		camera->down = matrix_vector_multi(matrix_rotation_relative(camera->right, \
			n_sin_rot()), camera->down);
	else if (key_code == NUMPAD_4)
		camera->right = matrix_vector_multi(matrix_rotation_relative(camera->down, \
			n_sin_rot()), camera->right);
	else if (key_code == NUMPAD_6)
		camera->right = matrix_vector_multi(matrix_rotation_relative(camera->down, \
			sin_rot()), camera->right);
	else if (key_code == NUMPAD_7)
		camera->right = matrix_vector_multi(matrix_rotation_relative(camera->front, \
			n_sin_rot()), camera->right);
	else
		camera->right = matrix_vector_multi(matrix_rotation_relative(camera->front, \
			sin_rot()), camera->right);
	if (key_code == NUMPAD_7 || key_code == NUMPAD_9)
		camera->down = cross_product(camera->front, camera->right);
	else
		camera->front = cross_product(camera->right, camera->down);
	update_scene(scene, CAMERA_ROTATION);
}

void	translation_absolute_camera(t_scene *scene, t_point vector)
{
	scene->camera->coord = add_vectors(scene->camera->coord, vector);
	update_scene(scene, CAMERA_TRANSLATION);
}

void	rotation_absolute_camera(t_scene *scene, t_matrix matrix)
{
	scene->camera->front = matrix_vector_multi(matrix, scene->camera->front);
	scene->camera->right = matrix_vector_multi(matrix, scene->camera->right);
	scene->camera->down = cross_product(scene->camera->front, scene->camera->right);
	update_scene(scene, CAMERA_ROTATION);
}

void	update_camera(t_scene *scene, unsigned int flags)
{
	t_camera	*camera;
	t_point		tmp;

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
