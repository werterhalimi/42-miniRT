/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 11:01:30 by ncotte            #+#    #+#             */
/*   Updated: 2023/01/29 11:01:32 by ncotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

#ifndef UNIT

int	main(int argc, char *argv[])
{
	t_scene	*scene;

	if (init(argc, argv, &scene))
		quit(scene);
	printf("%sSUCCESS!%s\n", BOLD_GREEN, RESET_COLOR);
	mlx_hook(scene->window, ON_KEYDOWN, 0, key_hook, scene);
	mlx_mouse_hook(scene->window, mouse_hook, scene);
	mlx_hook(scene->window, ON_DESTROY, 0, (void *)quit, scene);
	mlx_loop(scene->mlx);
}

#endif

#ifdef UNIT

int	main(int argc, char *argv[])
{
	(void) argc;
	(void) argv;
	printf("miniRT\n");
	return (0);
}
#endif
