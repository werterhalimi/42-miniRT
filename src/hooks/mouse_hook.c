/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 13:38:31 by ncotte            #+#    #+#             */
/*   Updated: 2023/02/22 00:18:17 by shalimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	select_object(int x, int y, t_scene *scene)
{
	t_point	ray;

	mlx_mouse_get_pos(scene->window, &x, &y);
	if (x < 0 || y < 0)
		return ;
	ray = unit_dist(add_vectors(add_vectors(scalar_multi(x, \
		scene->camera->shift_x), scalar_multi(y, \
		scene->camera->shift_y)), scene->window_corner), scene->camera->coord);
	find_intersect(scene, ray, NULL, &scene->index);
	write_type(scene);
}

static void	info_click(int x, int y, t_scene *scene)
{
	unsigned int	color;

	mlx_mouse_get_pos(scene->window, &x, &y);
	if (x < 0 || y < 0)
		return ;
	color = get_pixel_color(scene, x, y);
	printf("Click at ( %d, %d )\n", x, y);
	printf("Color : R = %u, G = %u, B = %u\n", color_get_r(color), \
		color_get_g(color), color_get_b(color));
/*
	t_point	pixel;
	printf("DEBUG\n");
	pixel = add_vectors(add_vectors(scalar_multi(x, \
		scene->camera->shift_x), scalar_multi(y, \
		scene->camera->shift_y)), scene->window_corner);
	find_color_pixel(scene, pixel, 10);*/
}

static void	scroll_hook(int mouse_code, t_scene *scene)
{
	if (!scene->index)
		fov_camera(mouse_code, scene);
	else if (scene->objects[scene->index - 1]->scroll)
		scene->objects[scene->index - 1]->scroll(mouse_code, scene);
	print_window(scene, PIXEL_RESOLUTION, 0);
}

int	mouse_hook(int mouse_code, int x, int y, t_scene *scene)
{
	if (mouse_code == SCROLL_UP || mouse_code == SCROLL_DOWN)
		scroll_hook(mouse_code, scene);
	else if (mouse_code == RIGHT_CLICK)
		info_click(x, y, scene);
	else if (mouse_code == LEFT_CLICK)
		select_object(x, y, scene);
	return (0);
}
