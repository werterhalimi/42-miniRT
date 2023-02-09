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

static void	print_info(t_scene *scene)
{
	printf("SCENE :\n");
	printf("Camera :\n");
	printf("Coord :\n");
	printf("x = %lf\n", scene->camera->coord.x);
	printf("y = %lf\n", scene->camera->coord.y);
	printf("z = %lf\n", scene->camera->coord.z);
	printf("Orientation :\n");
	printf("x = %lf\n", scene->camera->front.x);
	printf("y = %lf\n", scene->camera->front.y);
	printf("z = %lf\n", scene->camera->front.z);
	printf("FOV = %lf\n", scene->camera->fov);
	int i = -1;
	t_light *light;
	t_plane	*plane;
	t_sphere *sphere;
	t_cylinder *cylinder;
	printf("\nOBJECTS :\n");
	while (scene->objects[++i]) {
		printf("Type : %d\n", scene->objects[i]->type);
		if (scene->objects[i]->type == MAIN_LIGHT) {
			printf("Light :\n");
			light = (t_light *) (scene->objects[i]->object);
			printf("Coord :\n");
			printf("x = %lf\n", light->coord.x);
			printf("y = %lf\n", light->coord.y);
			printf("z = %lf\n", light->coord.z);
			printf("Ratio : %lf\n", light->ratio);
		} else if (scene->objects[i]->type == SPHERE) {
			printf("Sphere :\n");
			sphere = (t_sphere *) (scene->objects[i]->object);
			printf("Coord :\n");
			printf("x = %lf\n", sphere->coord.x);
			printf("y = %lf\n", sphere->coord.y);
			printf("z = %lf\n", sphere->coord.z);
			printf("Radius : %lf\n", sphere->radius);
		} else if (scene->objects[i]->type == PLANE) {
			printf("Plane :\n");
			plane = (t_plane *) (scene->objects[i]->object);
			printf("Coord :\n");
			printf("x = %lf\n", plane->coord.x);
			printf("y = %lf\n", plane->coord.y);
			printf("z = %lf\n", plane->coord.z);
			printf("Orientation :\n");
			printf("x = %lf\n", plane->normal.x);
			printf("y = %lf\n", plane->normal.y);
			printf("z = %lf\n", plane->normal.z);
		} else if (scene->objects[i]->type == CYLINDER) {
			printf("Cylinder :\n");
			cylinder = (t_cylinder *) (scene->objects[i]->object);
			printf("Coord :\n");
			printf("x = %lf\n", cylinder->coord.x);
			printf("y = %lf\n", cylinder->coord.y);
			printf("z = %lf\n", cylinder->coord.z);
			printf("Orientation :\n");
			printf("x = %lf\n", cylinder->direction.x);
			printf("y = %lf\n", cylinder->direction.y);
			printf("z = %lf\n", cylinder->direction.z);
		}
		printf("\n");
	}
}

int	key_hook(int key_code, t_scene *scene)
{
	printf("KEY = %d\n", key_code);
	if (key_code == KEY_ESC)
		quit(scene);
	if (key_code == KEY_SPACE)
		print_info(scene);
	if (key_code == KEY_W)
		scene->camera->coord = add_vectors(scene->camera->coord, \
            scalar_multi(0.01, scene->camera->front));
	if (key_code == KEY_S)
		scene->camera->coord = sub_vectors(scene->camera->coord, \
			scalar_multi(0.01, scene->camera->front));
	if (key_code == KEY_A)
		scene->camera->coord = sub_vectors(scene->camera->coord, \
			scalar_multi(0.01, scene->camera->right));
	if (key_code == KEY_D)
		scene->camera->coord = add_vectors(scene->camera->coord, \
			scalar_multi(0.01, scene->camera->right));
	if (key_code == KEY_R)
		scene->camera->coord = sub_vectors(scene->camera->coord, \
			scalar_multi(0.01, scene->camera->down));
	if (key_code == KEY_F)
		scene->camera->coord = add_vectors(scene->camera->coord, \
			scalar_multi(0.01, scene->camera->down));

	if (key_code == NUMPAD_2)
	{
		scene->camera->front = unit_vector(sub_vectors(scene->camera->front, \
            scalar_multi(0.01, scene->camera->down)));
		update_camera(scene, ROTATION_PITCH);
	}
	if (key_code == NUMPAD_8)
	{
		scene->camera->front = unit_vector(add_vectors(scene->camera->front, \
            scalar_multi(0.01, scene->camera->down)));
		update_camera(scene, ROTATION_PITCH);
	}
	if (key_code == NUMPAD_4)
	{
		scene->camera->front = unit_vector(sub_vectors(scene->camera->front, \
            scalar_multi(0.01, scene->camera->right)));
		update_camera(scene, ROTATION_YAW);
	}
	if (key_code == NUMPAD_6)
	{
		scene->camera->front = unit_vector(add_vectors(scene->camera->front, \
            scalar_multi(0.01, scene->camera->right)));
		update_camera(scene, ROTATION_YAW);
	}
	if (key_code == NUMPAD_7)
	{
		scene->camera->right = unit_vector(sub_vectors(scene->camera->right, \
            scalar_multi(0.01, scene->camera->down)));
		update_camera(scene, ROTATION_ROLL);
	}
	if (key_code == NUMPAD_9)
	{
		scene->camera->right = unit_vector(add_vectors(scene->camera->right, \
            scalar_multi(0.01, scene->camera->down)));
		update_camera(scene, ROTATION_ROLL);
	}
	print_window(scene);
	return (0);
}

int	mouse_hook(int mouse_code, int x, int y, t_scene *scene)
{
	printf("KEY = %d\n", mouse_code);
	if (mouse_code == RIGHT_CLICK)
	{
		mlx_mouse_get_pos(scene->window, &x, &y);
		printf("Click at ( %d, %d )\n", x, y);
	}
	if (mouse_code == SCROLL_UP && scene->camera->fov < M_PI)
	{
		printf("FOV\n");
		scene->camera->fov += 0.01;
		update_camera(scene, FOV);
	}
	if (mouse_code == SCROLL_DOWN && scene->camera->fov > 0.0)
	{
		printf("FOV\n");
		scene->camera->fov -= 0.01;
		update_camera(scene, FOV);
	}
	print_window(scene);
	return (0);
}
