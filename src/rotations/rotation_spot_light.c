/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation_spot_light.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 12:15:13 by ncotte            #+#    #+#             */
/*   Updated: 2023/02/16 12:15:16 by ncotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	rotation_relative_spot_light(int key_code, t_scene *scene)
{
	t_spot_light	*sl;

	sl = (t_spot_light *)scene->objects[scene->index - 1]->object;
	if (key_code == NUMPAD_2)
		sl->down = matrix_vector_multi(matrix_rotation(sl->right, \
			sin_rot()), sl->down);
	else if (key_code == NUMPAD_8)
		sl->down = matrix_vector_multi(matrix_rotation(sl->right, \
			n_sin_rot()), sl->down);
	else if (key_code == NUMPAD_4)
		sl->right = matrix_vector_multi(matrix_rotation(sl->down, \
			n_sin_rot()), sl->right);
	else if (key_code == NUMPAD_6)
		sl->right = matrix_vector_multi(matrix_rotation(sl->down, \
			sin_rot()), sl->right);
	else
		return ;
	sl->direction = cross_product(sl->right, sl->down);
	update_scene(scene, SPOT_LIGHT_ROTATION);
}

void	rotation_absolute_spot_light(t_scene *scene, t_matrix matrix)
{
	t_spot_light	*spot_light;

	spot_light = (t_spot_light *)scene->objects[scene->index - 1]->object;
	spot_light->direction = matrix_vector_multi(matrix, spot_light->direction);
	spot_light->right = matrix_vector_multi(matrix, spot_light->right);
	spot_light->down = cross_product(spot_light->direction, spot_light->right);
	update_scene(scene, SPOT_LIGHT_ROTATION);
}
