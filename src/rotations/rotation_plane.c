/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation_plane.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 14:10:41 by ncotte            #+#    #+#             */
/*   Updated: 2023/02/12 14:10:42 by ncotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	rotation_texture_plane(int key_code, \
				t_scene *scene, t_object *object, t_plane *plane)
{
	if (!object->texture && !object->normal_map && !object->color_bis)
		return ;
	if (key_code == NUMPAD_7)
		plane->right = matrix_vector_multi(matrix_rotation(plane->normal, \
			n_sin_rot()), plane->right);
	else
		plane->right = matrix_vector_multi(matrix_rotation(plane->normal, \
			sin_rot()), plane->right);
	plane->down = cross_product(plane->normal, plane->right);
	update_scene(scene, PLANE_ROTATION);
}

void	rotation_relative_plane(int key_code, t_scene *scene)
{
	t_object	*object;
	t_plane		*plane;

	object = scene->objects[scene->index - 1];
	plane = (t_plane *)object->object;
	if (key_code == NUMPAD_2)
		plane->down = matrix_vector_multi(matrix_rotation(plane->right, \
			sin_rot()), plane->down);
	else if (key_code == NUMPAD_8)
		plane->down = matrix_vector_multi(matrix_rotation(plane->right, \
			n_sin_rot()), plane->down);
	else if (key_code == NUMPAD_4)
		plane->right = matrix_vector_multi(matrix_rotation(plane->down, \
			n_sin_rot()), plane->right);
	else if (key_code == NUMPAD_6)
		plane->right = matrix_vector_multi(matrix_rotation(plane->down, \
			sin_rot()), plane->right);
	else
		return (rotation_texture_plane(key_code, scene, object, plane));
	plane->normal = cross_product(plane->right, plane->down);
	update_scene(scene, PLANE_ROTATION);
}

void	rotation_absolute_plane(t_scene *scene, t_matrix matrix)
{
	t_plane	*plane;

	plane = (t_plane *)scene->objects[scene->index - 1]->object;
	plane->normal = matrix_vector_multi(matrix, plane->normal);
	plane->right = matrix_vector_multi(matrix, plane->right);
	plane->down = cross_product(plane->normal, plane->right);
	update_scene(scene, PLANE_ROTATION);
}
