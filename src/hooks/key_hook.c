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

static void	print_info(t_scene *scene)
{
	int			i;
	t_light		*light;
	t_plane		*plane;
	t_sphere	*sphere;
	t_cylinder	*cylinder;

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
	printf("CAMERA_FOV = %lf\n", scene->camera->fov);
	printf("\nOBJECTS :\n");
	i = -1;
	while (scene->objects[++i])
	{
		printf("Type : %d\n", scene->objects[i]->type);
		if (scene->objects[i]->type == MAIN_LIGHT)
		{
			printf("Light :\n");
			light = (t_light *)(scene->objects[i]->object);
			printf("Coord :\n");
			printf("x = %lf\n", light->coord.x);
			printf("y = %lf\n", light->coord.y);
			printf("z = %lf\n", light->coord.z);
			printf("Ratio : %lf\n", light->ratio);
		}
		else if (scene->objects[i]->type == SPHERE)
		{
			printf("Sphere :\n");
			sphere = (t_sphere *)(scene->objects[i]->object);
			printf("Coord :\n");
			printf("x = %lf\n", sphere->coord.x);
			printf("y = %lf\n", sphere->coord.y);
			printf("z = %lf\n", sphere->coord.z);
			printf("Radius : %lf\n", sphere->radius);
		}
		else if (scene->objects[i]->type == PLANE)
		{
			printf("Plane :\n");
			plane = (t_plane *)(scene->objects[i]->object);
			printf("Coord :\n");
			printf("x = %lf\n", plane->coord.x);
			printf("y = %lf\n", plane->coord.y);
			printf("z = %lf\n", plane->coord.z);
			printf("Orientation :\n");
			printf("x = %lf\n", plane->normal.x);
			printf("y = %lf\n", plane->normal.y);
			printf("z = %lf\n", plane->normal.z);
		}
		else if (scene->objects[i]->type == CYLINDER)
		{
			printf("Cylinder :\n");
			cylinder = (t_cylinder *)(scene->objects[i]->object);
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

static t_point	vector_translation(int key_code)
{
	if (key_code == KEY_W)
		return (new_point(TRANSLATION_FACTOR, 0.0, 0.0));
	if (key_code == KEY_S)
		return (new_point(-TRANSLATION_FACTOR, 0.0, 0.0));
	if (key_code == KEY_A)
		return (new_point(0.0, TRANSLATION_FACTOR, 0.0));
	if (key_code == KEY_D)
		return (new_point(0.0, -TRANSLATION_FACTOR, 0.0));
	if (key_code == KEY_E)
		return (new_point(0.0, 0.0, TRANSLATION_FACTOR));
	return (new_point(0.0, 0.0, -TRANSLATION_FACTOR));
}

static t_matrix	matrix_rotation(int key_code)
{
	if (key_code == NUMPAD_8)
		return (new_matrix(new_point(cos_rot(), 0.0, sin_rot()), \
		new_point(0.0, 1.0, 0.0), \
		new_point(n_sin_rot(), 0.0, cos_rot())));
	if (key_code == NUMPAD_2)
		return (new_matrix(new_point(cos_rot(), 0.0, n_sin_rot()), \
		new_point(0.0, 1.0, 0.0), \
		new_point(sin_rot(), 0.0, cos_rot())));
	if (key_code == NUMPAD_4)
		return (new_matrix(new_point(cos_rot(), n_sin_rot(), 0.0), \
		new_point(sin_rot(), cos_rot(), 0.0), \
		new_point(0.0, 0.0, 1.0)));
	if (key_code == NUMPAD_6)
		return (new_matrix(new_point(cos_rot(), sin_rot(), 0.0), \
		new_point(n_sin_rot(), cos_rot(), 0.0), \
		new_point(0.0, 0.0, 1.0)));
	if (key_code == NUMPAD_7)
		return (new_matrix(new_point(1.0, 0.0, 0.0), \
			new_point(0.0, cos_rot(), sin_rot()), \
			new_point(0.0, n_sin_rot(), cos_rot())));
	return (new_matrix(new_point(1.0, 0.0, 0.0), \
		new_point(0.0, cos_rot(), n_sin_rot()), \
		new_point(0.0, sin_rot(), cos_rot())));
}

static void	translation(int key_code, t_scene *scene)
{
	t_point	vector;

	if (scene->mode == ABSOLUTE)
		vector = vector_translation(key_code);
	if (!scene->index && scene->mode == RELATIVE)
		translation_relative_camera(key_code, scene);
	else if (!scene->index)
		translation_absolute_camera(scene, vector);
	else if (scene->mode == RELATIVE \
		&& scene->objects[scene->index - 1]->translation_relative)
		scene->objects[scene->index - 1]->translation_relative(key_code, scene);
	else if (scene->mode == ABSOLUTE \
		&& scene->objects[scene->index - 1]->translation_absolute)
		scene->objects[scene->index - 1]->translation_absolute(scene, vector);
}

static void	rotation(int key_code, t_scene *scene)
{
	t_matrix	matrix;

	if (scene->mode == ABSOLUTE)
		matrix = matrix_rotation(key_code);
	if (!scene->index && scene->mode == RELATIVE)
		rotation_relative_camera(key_code, scene);
	else if (!scene->index)
		rotation_absolute_camera(scene, matrix);
	else if (scene->mode == RELATIVE \
		&& scene->objects[scene->index - 1]->rotation_relative)
		scene->objects[scene->index - 1]->rotation_relative(key_code, scene);
	else if (scene->mode == ABSOLUTE \
		&& scene->objects[scene->index - 1]->rotation_absolute)
		scene->objects[scene->index - 1]->rotation_absolute(scene, matrix);
}

static void	change_mode(t_scene *scene)
{
	scene->mode = !scene->mode;
	if (scene->mode)
		printf("You are now in absolute mode\n");
	else
		printf("You are now in relative mode\n");
}

int	key_hook(int key_code, t_scene *scene)
{
	printf("KEY = %d\n", key_code);
	if (key_code == KEY_ESC)
		quit(scene);
	else if (key_code == KEY_SPACE)
		print_info(scene);
	else if (is_key_translation(key_code))
		translation(key_code, scene);
	else if (is_key_rotation(key_code))
		rotation(key_code, scene);
	else if (key_code == KEY_TAB)
		change_mode(scene);
	else if (key_code == KEY_PAGE_UP)
		scene->index = (scene->index + 1) % (scene->nb_objects + 1);
	else if (key_code == KEY_PAGE_DOWN)
		scene->index = (scene->index - 1) % (scene->nb_objects + 1);
	print_window(scene);
	return (0);
}
