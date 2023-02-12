/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation_camera.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 14:10:26 by ncotte            #+#    #+#             */
/*   Updated: 2023/02/12 14:10:28 by ncotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static t_point	vector_rotation(t_point vector, t_point axis, double sinus)
{
	return (matrix_vector_multi(matrix_rotation(axis, sinus), vector));
}

void	rotation_relative_camera(int key_code, t_scene *scene)
{
	t_camera	*ca;

	ca = scene->camera;
	if (key_code == NUMPAD_2)
		ca->down = vector_rotation(ca->down, ca->right, sin_rot());
	else if (key_code == NUMPAD_8)
		ca->down = vector_rotation(ca->down, ca->right, n_sin_rot());
	else if (key_code == NUMPAD_4)
		ca->right = vector_rotation(ca->right, ca->down, n_sin_rot());
	else if (key_code == NUMPAD_6)
		ca->right = vector_rotation(ca->right, ca->down, sin_rot());
	else if (key_code == NUMPAD_7)
		ca->right = vector_rotation(ca->right, ca->front, n_sin_rot());
	else
		ca->right = vector_rotation(ca->right, ca->front, sin_rot());
	if (key_code == NUMPAD_7 || key_code == NUMPAD_9)
		ca->down = cross_product(ca->front, ca->right);
	else
		ca->front = cross_product(ca->right, ca->down);
	update_scene(scene, CAMERA_ROTATION);
}

void	rotation_absolute_camera(t_scene *scene, t_matrix matrix)
{
	scene->camera->front = matrix_vector_multi(matrix, scene->camera->front);
	scene->camera->right = matrix_vector_multi(matrix, scene->camera->right);
	scene->camera->down = cross_product(scene->camera->front, \
		scene->camera->right);
	update_scene(scene, CAMERA_ROTATION);
}
