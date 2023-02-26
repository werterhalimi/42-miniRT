/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 11:01:30 by ncotte            #+#    #+#             */
/*   Updated: 2023/02/14 23:29:02 by shalimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	main(int argc, char *argv[])
{
	t_scene	*scene;

	if (init(argc, argv, &scene))
		quit(scene);
	mlx_hook(scene->window, ON_KEYDOWN, 0, key_hook, scene);
	mlx_key_hook(scene->window, key_release, scene);
	mlx_mouse_hook(scene->window, mouse_hook, scene);
	mlx_hook(scene->window, ON_MOUSEUP, 0, mouse_release, scene);
	mlx_hook(scene->window, ON_DESTROY, 0, (void *)quit, scene);
	mlx_loop(scene->mlx);
}
