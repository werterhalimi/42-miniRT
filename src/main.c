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

static void	quit(t_scene *scene)
{
	printf("Scene : %p\n", scene);
	printf("Mlx : %p\n", scene->mlx);
	printf("Windows : %p\n", scene->win);
	printf("Image : %p\n", scene->img);
	printf("Address : %p\n", scene->addr);
//	free(scene->addr); // TODO double free ??
	if (scene->win)
		mlx_destroy_window(scene->mlx, scene->win);
	if (scene->img)
		mlx_destroy_image(scene->mlx, scene->img);
	free(scene->mlx);
	ft_flush();
	exit(SUCCESS);
}

#ifndef UNIT

int	main(int argc, char *argv[])
{
	t_scene	*scene;

	if (init(argc, argv, &scene))
		quit(scene);
	printf("%sSUCCESS!%s\n", BOLD_GREEN, RESET_COLOR);
	mlx_hook(scene->win, ON_DESTROY, 0, (void *)quit, scene);
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
