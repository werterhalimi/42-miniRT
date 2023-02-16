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

void	rotation_relative_plane(int key_code, t_scene *scene)
{
	t_plane	*pl;

	pl = (t_plane *)scene->objects[scene->index - 1]->object;
	if (key_code == NUMPAD_2)
		pl->down = matrix_vector_multi(matrix_rotation(pl->right, \
			sin_rot()), pl->down);
	else if (key_code == NUMPAD_8)
		pl->down = matrix_vector_multi(matrix_rotation(pl->right, \
			n_sin_rot()), pl->down);
	else if (key_code == NUMPAD_4)
		pl->right = matrix_vector_multi(matrix_rotation(pl->down, \
			n_sin_rot()), pl->right);
	else if (key_code == NUMPAD_6)
		pl->right = matrix_vector_multi(matrix_rotation(pl->down, \
			sin_rot()), pl->right);
	else
		return ;
	pl->normal = cross_product(pl->right, pl->down);
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
