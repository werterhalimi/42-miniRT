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

void	rotation_relative_cylinder(int key_code, t_scene *scene)
{
	t_cylinder	*cy;

	cy = (t_cylinder *)scene->objects[scene->index - 1]->object;
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
		return ;
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
