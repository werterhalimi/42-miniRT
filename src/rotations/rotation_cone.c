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

void	rotation_relative_cone(int key_code, t_scene *scene)
{
	t_cone	*co;

	co = (t_cone *)(scene->objects[scene->index - 1]->object);
	if (key_code == NUMPAD_2)
		co->down = matrix_vector_multi(matrix_rotation(co->right, \
			sin_rot()), co->down);
	else if (key_code == NUMPAD_8)
		co->down = matrix_vector_multi(matrix_rotation(co->right, \
			n_sin_rot()), co->down);
	else if (key_code == NUMPAD_4)
		co->right = matrix_vector_multi(matrix_rotation(co->down, \
			n_sin_rot()), co->right);
	else if (key_code == NUMPAD_6)
		co->right = matrix_vector_multi(matrix_rotation(co->down, \
			sin_rot()), co->right);
	else
		return ;
	co->direction = cross_product(co->right, co->down);
	update_scene(scene, CONE_ROTATION);
}

void	rotation_absolute_cone(t_scene *scene, t_matrix matrix)
{
	t_cone	*cone;

	cone = (t_cone *)(scene->objects[scene->index - 1]->object);
	cone->direction = matrix_vector_multi(matrix, cone->direction);
	cone->right = matrix_vector_multi(matrix, cone->right);
	cone->down = cross_product(cone->direction, cone->right);
	update_scene(scene, CONE_ROTATION);
}
