/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation_sphere.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 18:56:39 by ncotte            #+#    #+#             */
/*   Updated: 2023/02/26 18:56:41 by ncotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	rotation_roll_sphere(int key_code, \
				t_scene *scene, t_sphere *sphere)
{
	if (key_code == NUMPAD_7)
		sphere->right = matrix_vector_multi(matrix_rotation(sphere->front, \
			n_sin_rot()), sphere->right);
	else
		sphere->right = matrix_vector_multi(matrix_rotation(sphere->front, \
			sin_rot()), sphere->right);
	sphere->down = cross_product(sphere->front, sphere->right);
	update_scene(scene, SPHERE_ROTATION);
}

void	rotation_relative_sphere(int key_code, t_scene *scene)
{
	t_object	*object;
	t_sphere	*sphere;

	object = scene->objects[scene->index - 1];
	if (!object->texture && !object->normal_map && !object->color_bis)
		return ;
	sphere = (t_sphere *)object->object;
	if (key_code == NUMPAD_2)
		sphere->down = matrix_vector_multi(matrix_rotation(sphere->right, \
			sin_rot()), sphere->down);
	else if (key_code == NUMPAD_8)
		sphere->down = matrix_vector_multi(matrix_rotation(sphere->right, \
			n_sin_rot()), sphere->down);
	else if (key_code == NUMPAD_4)
		sphere->right = matrix_vector_multi(matrix_rotation(sphere->down, \
			n_sin_rot()), sphere->right);
	else if (key_code == NUMPAD_6)
		sphere->right = matrix_vector_multi(matrix_rotation(sphere->down, \
			sin_rot()), sphere->right);
	else
		return (rotation_roll_sphere(key_code, scene, sphere));
	sphere->front = cross_product(sphere->right, sphere->down);
	update_scene(scene, SPHERE_ROTATION);
}

void	rotation_absolute_sphere(t_scene *scene, t_matrix matrix)
{
	t_object	*object;
	t_sphere	*sphere;

	object = scene->objects[scene->index - 1];
	if (!object->texture && !object->normal_map && !object->color_bis)
		return ;
	sphere = (t_sphere *)scene->objects[scene->index - 1]->object;
	sphere->front = matrix_vector_multi(matrix, sphere->front);
	sphere->right = matrix_vector_multi(matrix, sphere->right);
	sphere->down = cross_product(sphere->front, sphere->right);
	update_scene(scene, SPHERE_ROTATION);
}
