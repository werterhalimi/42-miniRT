/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 14:16:01 by ncotte            #+#    #+#             */
/*   Updated: 2023/02/12 14:16:02 by ncotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static t_matrix	matrix_rotation_absolute(int key_code)
{
	if (key_code == NUMPAD_8)
		return (new_matrix(new_point(cos_rot(), 0.0, sin_rot()), \
		new_point(0.0, 1.0, 0.0), \
		new_point(n_sin_rot(), 0.0, cos_rot())));
	if (key_code == NUMPAD_2)
		return (new_matrix(new_point(cos_rot(), 0.0, n_sin_rot()), \
		new_point(0.0, 1.0, 0.0), \
		new_point(sin_rot(), 0.0, cos_rot())));
	if (key_code == NUMPAD_4)
		return (new_matrix(new_point(cos_rot(), n_sin_rot(), 0.0), \
		new_point(sin_rot(), cos_rot(), 0.0), \
		new_point(0.0, 0.0, 1.0)));
	if (key_code == NUMPAD_6)
		return (new_matrix(new_point(cos_rot(), sin_rot(), 0.0), \
		new_point(n_sin_rot(), cos_rot(), 0.0), \
		new_point(0.0, 0.0, 1.0)));
	if (key_code == NUMPAD_7)
		return (new_matrix(new_point(1.0, 0.0, 0.0), \
			new_point(0.0, cos_rot(), sin_rot()), \
			new_point(0.0, n_sin_rot(), cos_rot())));
	return (new_matrix(new_point(1.0, 0.0, 0.0), \
		new_point(0.0, cos_rot(), n_sin_rot()), \
		new_point(0.0, sin_rot(), cos_rot())));
}

void	rotation(int key_code, t_scene *scene)
{
	t_matrix	matrix;

	if (scene->mode == ABSOLUTE)
		matrix = matrix_rotation_absolute(key_code);
	if (!scene->index && scene->mode == RELATIVE)
		rotation_relative_camera(key_code, scene);
	else if (!scene->index)
		rotation_absolute_camera(scene, matrix);
	else if (scene->mode == RELATIVE \
		&& scene->objects[scene->index - 1]->rotation_relative)
		scene->objects[scene->index - 1]->rotation_relative(key_code, scene);
	else if (scene->mode == ABSOLUTE \
		&& scene->objects[scene->index - 1]->rotation_absolute)
		scene->objects[scene->index - 1]->rotation_absolute(scene, matrix);
}
