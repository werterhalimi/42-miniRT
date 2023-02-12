/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 13:38:31 by ncotte            #+#    #+#             */
/*   Updated: 2023/02/10 13:38:32 by ncotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	select_object(int x, int y, t_scene *scene)
{
	t_point	ray;

	mlx_mouse_get_pos(scene->window, &x, &y);
	ray = unit_vector(add_vectors(add_vectors(scalar_multi(x, \
		scene->camera->shift_x), scalar_multi(y, \
		scene->camera->shift_y)), scene->window_corner));
	find_intersect(scene, ray, &scene->index);
	write_type(scene);
}

static void	update_radius(int mouse_code, t_scene *scene)
{
	t_sphere	*sphere;

	sphere = (t_sphere *)(scene->objects[scene->index - 1]->object);
	if (mouse_code == SCROLL_UP)
		sphere->radius *= (1 + RADIUS_FACTOR);
	else if (sphere->radius > 0.0)
		sphere->radius *= (1 - RADIUS_FACTOR);
	update_scene(scene, SPHERE_RADIUS);
}

static void	update_height(int mouse_code, t_scene *scene)
{
	t_cylinder	*cylinder;

	cylinder = (t_cylinder *)(scene->objects[scene->index - 1]->object);
	if (mouse_code == SCROLL_UP)
		cylinder->semi_height *= (1 + HEIGHT_FACTOR);
	else if (cylinder->radius > 0.0)
		cylinder->semi_height *= (1 - HEIGHT_FACTOR);
	update_scene(scene, CYLINDER_HEIGHT);
}

static void	scroll_hook(int mouse_code, t_scene *scene)
{
	if (!scene->index)
	{
		if (mouse_code == SCROLL_UP && scene->camera->fov < M_PI - FOV_FACTOR)
			scene->camera->fov += FOV_FACTOR;
		else if (mouse_code == SCROLL_DOWN && scene->camera->fov > FOV_FACTOR)
			scene->camera->fov -= FOV_FACTOR;
		update_camera(scene, CAMERA_FOV);
	}
	else if (scene->objects[scene->index - 1]->type == SPHERE)
		update_radius(mouse_code, scene);
	else if (scene->objects[scene->index - 1]->type == CYLINDER)
		update_height(mouse_code, scene);
}

int	mouse_hook(int mouse_code, int x, int y, t_scene *scene)
{
//	printf("MOUSE = %d\n", mouse_code);
	if (mouse_code == SCROLL_UP || mouse_code == SCROLL_DOWN)
	{
		scroll_hook(mouse_code, scene);
		print_window(scene, 10);
	}
	else if (mouse_code == RIGHT_CLICK)
	{
		mlx_mouse_get_pos(scene->window, &x, &y);
		printf("Click at ( %d, %d )\n", x, y);
		printf("Color : %u\n", get_pixel_color(scene, x, y));
	}
	else if (mouse_code == LEFT_CLICK)
		select_object(x, y, scene);
	return (0);
}
