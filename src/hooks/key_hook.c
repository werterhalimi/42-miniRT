/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 17:25:52 by ncotte            #+#    #+#             */
/*   Updated: 2023/02/01 17:25:54 by ncotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	update_mode(int key_code, t_scene *scene)
{
	if (key_code == KEY_TAB)
	{
		scene->mode = !scene->mode;
		if (scene->mode)
			printf("You are now in absolute mode\n");
		else
			printf("You are now in relative mode\n");
	}
	else
	{
		if (key_code == KEY_PAGE_UP)
			scene->index = (scene->index + 1) % (scene->nb_objects + 1);
		else
			scene->index = (scene->index - 1) % (scene->nb_objects + 1);
		write_type(scene);
	}
}

static void	update_radius(int key_code, t_scene *scene)
{
	t_cylinder	*cylinder;

	cylinder = (t_cylinder *)(scene->objects[scene->index - 1]->object);
	if (key_code == NUMPAD_PLUS)
		cylinder->radius *= (1 + RADIUS_FACTOR);
	else if (cylinder->radius > 0.0)
		cylinder->radius *= (1 - RADIUS_FACTOR);
	update_scene(scene, CYLINDER_RADIUS);
}

static void	update_numpad(int key_code, t_scene *scene)
{
	if (!scene->index && key_code == NUMPAD_PLUS \
		&& scene->amb_light->ratio <= 1 - LIGHT_RATIO_FACTOR)
		scene->amb_light->ratio += LIGHT_RATIO_FACTOR;
	else if (!scene->index && key_code == NUMPAD_MINUS \
		&& scene->amb_light->ratio >= LIGHT_RATIO_FACTOR)
		scene->amb_light->ratio -= LIGHT_RATIO_FACTOR;
	else if (scene->index == 1 && key_code == NUMPAD_PLUS \
		&& scene->light->ratio <= 1 - LIGHT_RATIO_FACTOR)
		scene->light->ratio += LIGHT_RATIO_FACTOR;
	else if (scene->index == 1 && key_code == NUMPAD_MINUS \
		&& scene->light->ratio >= LIGHT_RATIO_FACTOR)
		scene->light->ratio -= LIGHT_RATIO_FACTOR;
	else if (scene->index && scene->objects[scene->index - 1]->type == CYLINDER)
		update_radius(key_code, scene);
	print_window(scene, 10);
}

int	key_hook(int key_code, t_scene *scene)
{
//	printf("KEY = %d\n", key_code);
	if (key_code == KEY_ESC)
		quit(scene);
	else if (key_code == KEY_SPACE)
		write_info(scene);
	else if (is_key_translation(key_code))
		translation(key_code, scene);
	else if (is_key_rotation(key_code))
		rotation(key_code, scene);
	else if (key_code == NUMPAD_PLUS || key_code == NUMPAD_MINUS)
		update_numpad(key_code, scene);
	else if (key_code == KEY_TAB || key_code == KEY_PAGE_UP \
		|| key_code == KEY_PAGE_DOWN)
		update_mode(key_code, scene);
	return (0);
}
