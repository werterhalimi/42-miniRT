/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 14:16:09 by ncotte            #+#    #+#             */
/*   Updated: 2023/02/12 14:16:11 by ncotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static t_point	vector_translation(int key_code)
{
	if (key_code == KEY_W)
		return (new_point(TRANSLATION_FACTOR, 0.0, 0.0));
	if (key_code == KEY_S)
		return (new_point(-TRANSLATION_FACTOR, 0.0, 0.0));
	if (key_code == KEY_A)
		return (new_point(0.0, TRANSLATION_FACTOR, 0.0));
	if (key_code == KEY_D)
		return (new_point(0.0, -TRANSLATION_FACTOR, 0.0));
	if (key_code == KEY_E)
		return (new_point(0.0, 0.0, TRANSLATION_FACTOR));
	return (new_point(0.0, 0.0, -TRANSLATION_FACTOR));
}

void	translation(int key_code, t_scene *scene)
{
	t_point	vector;

	if (scene->mode == ABSOLUTE)
		vector = vector_translation(key_code);
	if (!scene->index && scene->mode == RELATIVE)
		translation_relative_camera(key_code, scene);
	else if (!scene->index)
		translation_absolute_camera(scene, vector);
	else if (scene->mode == RELATIVE \
		&& scene->objects[scene->index - 1]->translation_relative)
		scene->objects[scene->index - 1]->translation_relative(key_code, scene);
	else if (scene->mode == ABSOLUTE \
		&& scene->objects[scene->index - 1]->translation_absolute)
		scene->objects[scene->index - 1]->translation_absolute(scene, vector);
}
