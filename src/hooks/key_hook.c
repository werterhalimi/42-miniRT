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

static void	update_mode(t_scene *scene)
{
	scene->mode = !scene->mode;
	if (scene->mode)
		printf("You are now in absolute mode\n");
	else
		printf("You are now in relative mode\n");
}

static void	update_selection(int key_code, t_scene *scene)
{
	if (key_code == KEY_PAGE_UP)
		scene->index = (scene->index + 1) % (scene->nb_objects + 1);
	else
		scene->index = (scene->index - 1) % (scene->nb_objects + 1);
	write_type(scene);
}

static void	update_numpad(int key_code, t_scene *scene)
{
	if (!scene->index)
		ratio_amb_light(key_code, scene);
	else if (scene->objects[scene->index - 1]->numpad_plus_minus)
		scene->objects[scene->index - 1]->numpad_plus_minus(key_code, scene);
	print_window(scene, PIXEL_RESOLUTION);
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
	else if (key_code == KEY_TAB)
		update_mode(scene);
	else if (key_code == KEY_PAGE_UP || key_code == KEY_PAGE_DOWN)
		update_selection(key_code, scene);
	return (0);
}
