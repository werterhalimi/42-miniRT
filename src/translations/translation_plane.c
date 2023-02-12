/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translation_plane.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 14:02:59 by ncotte            #+#    #+#             */
/*   Updated: 2023/02/12 14:03:01 by ncotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

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

void	translation_absolute_plane(t_scene *scene, t_point vector)
{
	t_plane	*plane;

	plane = (t_plane *)(scene->objects[scene->index - 1]->object);
	plane->coord = add_vectors(plane->coord, vector);
	update_scene(scene, PLANE_TRANSLATION);
}
