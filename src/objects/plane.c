/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 19:27:46 by ncotte            #+#    #+#             */
/*   Updated: 2023/01/29 19:27:48 by ncotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	is_plane(t_point point, t_plane plane)
{
	if (dot_product(sub_vectors(point, plane.coord), plane.normal))
		return (NO);
	return (YES);
}

void	update_plane(t_scene *scene, void *object, unsigned int flags)
{
	t_plane	*plane;

	if (!(flags & (CAMERA_TRANSLATION | PLANE_ALL)))
		return ;
	plane = (t_plane *)object;
	plane->value = dot_product(sub_vectors(plane->coord, \
		scene->camera->coord), plane->normal);
}

double	intersect_plane(t_point ray, void *object)
{
	t_plane	*plane;
	double	div;
	double	t;

	plane = (t_plane *)object;
	div = dot_product(ray, plane->normal);
	if (!div)
		return (INFINITY);
	t = plane->value / div;
	if (t < 0.0)
		return (INFINITY);
	return (t);
}

void	translation_relative_plane(int key_code, t_scene *scene)
{
	t_point	vector;
	t_plane	*plane;

	plane = (t_plane *)(scene->objects[scene->index - 1]->object);
	if (key_code == KEY_W)
		vector = scalar_multi(TRANSLATION_FACTOR, plane->normal);
	else if (key_code == KEY_S)
		vector = scalar_multi(-TRANSLATION_FACTOR, plane->normal);
	else
		return ;
	plane->coord = add_vectors(plane->coord, vector);
	update_scene(scene, PLANE_TRANSLATION);
}

void	rotation_relative_plane(int key_code, t_scene *scene)
{
	t_plane 	*plane;

	plane = (t_plane *)(scene->objects[scene->index - 1]->object);
	if (key_code == NUMPAD_2)
		plane->down = matrix_vector_multi(matrix_rotation_relative(plane->right, \
			sin_rot()), plane->down);
	else if (key_code == NUMPAD_8)
		plane->down = matrix_vector_multi(matrix_rotation_relative(plane->right, \
			n_sin_rot()), plane->down);
	else if (key_code == NUMPAD_4)
		plane->right = matrix_vector_multi(matrix_rotation_relative(plane->down, \
			n_sin_rot()), plane->right);
	else if (key_code == NUMPAD_6)
		plane->right = matrix_vector_multi(matrix_rotation_relative(plane->down, \
			sin_rot()), plane->right);
	else
		return ;
	plane->normal = cross_product(plane->right, plane->down);
	update_scene(scene, PLANE_ROTATION);
}

void	translation_absolute_plane(t_scene *scene, t_point vector)
{
	t_plane	*plane;

	plane = (t_plane *)(scene->objects[scene->index - 1]->object);
	plane->coord = add_vectors(plane->coord, vector);
	update_scene(scene, PLANE_TRANSLATION);
}

void	rotation_absolute_plane(t_scene *scene, t_matrix matrix)
{
	t_plane	*plane;

	plane = (t_plane *)(scene->objects[scene->index - 1]->object);
	plane->normal = matrix_vector_multi(matrix, plane->normal);
	plane->right = matrix_vector_multi(matrix, plane->right);
	plane->down = cross_product(plane->normal, plane->right);
	update_scene(scene, PLANE_ROTATION);
}

unsigned int	get_color_plane(t_scene *scene, void *object)
{
	t_plane	*plane;

	(void)scene;
	plane = (t_plane *)object;
	return (color_trgb(plane->color));
}
