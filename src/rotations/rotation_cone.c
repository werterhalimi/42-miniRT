/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation_cone.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 17:32:10 by ncotte            #+#    #+#             */
/*   Updated: 2023/02/13 17:32:12 by ncotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	rotation_texture_cone(int key_code, \
				t_scene *scene, t_object *object, t_cone *cone)
{
	if (!object->texture && !object->normal_map && !object->color_bis)
		return ;
	if (key_code == NUMPAD_7)
		cone->right = matrix_vector_multi(matrix_rotation(cone->direction, \
			n_sin_rot()), cone->right);
	else
		cone->right = matrix_vector_multi(matrix_rotation(cone->direction, \
			sin_rot()), cone->right);
	cone->down = cross_product(cone->direction, cone->right);
	update_scene(scene, CONE_ROTATION);
}

void	rotation_relative_cone(int key_code, t_scene *scene)
{
	t_object	*object;
	t_cone		*cone;

	object = scene->objects[scene->index - 1];
	cone = (t_cone *)object->object;
	if (key_code == NUMPAD_2)
		cone->down = matrix_vector_multi(matrix_rotation(cone->right, \
			sin_rot()), cone->down);
	else if (key_code == NUMPAD_8)
		cone->down = matrix_vector_multi(matrix_rotation(cone->right, \
			n_sin_rot()), cone->down);
	else if (key_code == NUMPAD_4)
		cone->right = matrix_vector_multi(matrix_rotation(cone->down, \
			n_sin_rot()), cone->right);
	else if (key_code == NUMPAD_6)
		cone->right = matrix_vector_multi(matrix_rotation(cone->down, \
			sin_rot()), cone->right);
	else
		return (rotation_texture_cone(key_code, scene, object, cone));
	cone->direction = cross_product(cone->right, cone->down);
	update_scene(scene, CONE_ROTATION);
}

void	rotation_absolute_cone(t_scene *scene, t_matrix matrix)
{
	t_cone	*cone;

	cone = (t_cone *)scene->objects[scene->index - 1]->object;
	cone->direction = matrix_vector_multi(matrix, cone->direction);
	cone->right = matrix_vector_multi(matrix, cone->right);
	cone->down = cross_product(cone->direction, cone->right);
	update_scene(scene, CONE_ROTATION);
}
