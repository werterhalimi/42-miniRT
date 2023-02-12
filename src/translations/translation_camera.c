/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translation_camera.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 14:02:35 by ncotte            #+#    #+#             */
/*   Updated: 2023/02/12 14:02:37 by ncotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	translation_relative_camera(int key_code, t_scene *scene)
{
	t_point	vector;

	if (key_code == KEY_W)
		vector = scalar_multi(TRANSLATION_FACTOR, scene->camera->front);
	else if (key_code == KEY_S)
		vector = scalar_multi(-TRANSLATION_FACTOR, scene->camera->front);
	else if (key_code == KEY_A)
		vector = scalar_multi(-TRANSLATION_FACTOR, scene->camera->right);
	else if (key_code == KEY_D)
		vector = scalar_multi(TRANSLATION_FACTOR, scene->camera->right);
	else if (key_code == KEY_E)
		vector = scalar_multi(-TRANSLATION_FACTOR, scene->camera->down);
	else
		vector = scalar_multi(TRANSLATION_FACTOR, scene->camera->down);
	scene->camera->coord = add_vectors(scene->camera->coord, vector);
	update_scene(scene, CAMERA_TRANSLATION);
}

void	translation_absolute_camera(t_scene *scene, t_point vector)
{
	scene->camera->coord = add_vectors(scene->camera->coord, vector);
	update_scene(scene, CAMERA_TRANSLATION);
}
