/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation_cylinder.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 14:10:35 by ncotte            #+#    #+#             */
/*   Updated: 2023/02/12 14:10:36 by ncotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	rotation_texture_cylinder(int key_code, \
				t_scene *scene, t_object *object, t_cylinder *cy)
{
	if (!object->texture && !object->normal_map && !object->color_bis)
		return ;
	if (key_code == NUMPAD_7)
		cy->right = matrix_vector_multi(matrix_rotation(cy->direction, \
			n_sin_rot()), cy->right);
	else
		cy->right = matrix_vector_multi(matrix_rotation(cy->direction, \
			sin_rot()), cy->right);
	cy->down = cross_product(cy->direction, cy->right);
	update_scene(scene, CYLINDER_ROTATION);
}

void	rotation_relative_cylinder(int key_code, t_scene *scene)
{
	t_object	*object;
	t_cylinder	*cy;

	object = scene->objects[scene->index - 1];
	cy = (t_cylinder *)object->object;
	if (key_code == NUMPAD_2)
		cy->down = matrix_vector_multi(matrix_rotation(cy->right, \
			sin_rot()), cy->down);
	else if (key_code == NUMPAD_8)
		cy->down = matrix_vector_multi(matrix_rotation(cy->right, \
			n_sin_rot()), cy->down);
	else if (key_code == NUMPAD_4)
		cy->right = matrix_vector_multi(matrix_rotation(cy->down, \
			n_sin_rot()), cy->right);
	else if (key_code == NUMPAD_6)
		cy->right = matrix_vector_multi(matrix_rotation(cy->down, \
			sin_rot()), cy->right);
	else
		return (rotation_texture_cylinder(key_code, scene, object, cy));
	cy->direction = cross_product(cy->right, cy->down);
	update_scene(scene, CYLINDER_ROTATION);
}

void	rotation_absolute_cylinder(t_scene *scene, t_matrix matrix)
{
	t_cylinder	*cylinder;

	cylinder = (t_cylinder *)scene->objects[scene->index - 1]->object;
	cylinder->direction = matrix_vector_multi(matrix, cylinder->direction);
	cylinder->right = matrix_vector_multi(matrix, cylinder->right);
	cylinder->down = cross_product(cylinder->direction, cylinder->right);
	update_scene(scene, CYLINDER_ROTATION);
}
