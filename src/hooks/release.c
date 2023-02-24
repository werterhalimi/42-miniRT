/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   release.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 16:59:53 by ncotte            #+#    #+#             */
/*   Updated: 2023/02/12 16:59:55 by ncotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	key_release(int key_code, t_scene *scene)
{
	if (key_code == NUMPAD_ENTER && scene->axis)
		print_graduation(scene);
	else if (key_code == NUMPAD_ENTER)
		mlx_put_image_to_window(scene->mlx, scene->window, \
			scene->main_img->ptr, 0, 0);
	else if (is_key_rotation(key_code) || is_key_translation(key_code) \
		|| key_code == NUMPAD_PLUS || key_code == NUMPAD_MINUS \
		|| key_code == KEY_SPACE)
		print_window(scene, 1, scene->reflexions);
	return (0);
}

int	mouse_release(int mouse_code, int x, int y, t_scene *scene)
{
	(void) x;
	(void) y;
	if (mouse_code != LEFT_CLICK && mouse_code != RIGHT_CLICK)
		print_window(scene, 1, scene->reflexions);
	return (0);
}
