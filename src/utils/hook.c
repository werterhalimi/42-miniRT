/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 17:25:52 by ncotte            #+#    #+#             */
/*   Updated: 2023/02/01 17:25:54 by ncotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	key_hook(int key_code, t_scene *scene)
{
	if (key_code == KEY_ESC)
		quit(scene);
	if (key_code == KEY_SPACE)
	{
		printf("SCENE :\n");
		printf("Ambient light :\n");
		printf("Color :\n");
		printf("Red   = %d\n", scene->amb_light->color.r);
		printf("Green = %d\n", scene->amb_light->color.g);
		printf("Blue  = %d\n", scene->amb_light->color.b);
		print_window(scene);
	}
	return (0);
}

int	mouse_hook(int mouse_code, int x, int y, t_scene *scene)
{
	if (mouse_code == RIGHT_CLICK)
	{
		mlx_mouse_get_pos(scene->window, &x, &y);
		printf("Click at ( %d, %d )\n", x, y);
	}
	return (0);
}
