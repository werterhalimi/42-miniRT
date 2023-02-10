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
	vector = new_point(0.0, 0.0, 0.0);
	if (key_code == KEY_W)
		vector = scalar_multi(TRANSLATION_FACTOR, plane->normal);
	else if (key_code == KEY_S)
		vector = scalar_multi(-TRANSLATION_FACTOR, plane->normal);
	plane->coord = add_vectors(plane->coord, vector);
	update_scene(scene, PLANE_TRANSLATION);
}

void	rotation_relative_plane(int key_code, t_scene *scene)
{
	(void) key_code;
	(void) scene;
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
	update_scene(scene, PLANE_ROTATION);
}

unsigned int	get_color_plane(t_scene *scene, void *object)
{
	t_plane	*plane;

	(void)scene;
	plane = (t_plane *)object;
	return (color_trgb(plane->color));
}
