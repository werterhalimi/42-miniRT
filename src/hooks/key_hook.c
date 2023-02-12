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
			printf("Radius : %lf\n", cylinder->radius);
			printf("Height : %lf\n", cylinder->semi_height);
		}
		printf("\n");
	}
}

static void	change_mode(t_scene *scene)
{
	scene->mode = !scene->mode;
	if (scene->mode)
		printf("You are now in absolute mode\n");
	else
		printf("You are now in relative mode\n");
}

static void	update_radius(int key_code, t_scene *scene)
{
	t_cylinder	*cylinder;

	cylinder = (t_cylinder *)(scene->objects[scene->index - 1]->object);
	if (key_code == NUMPAD_PLUS)
		cylinder->radius *= (1 + RADIUS_FACTOR);
	else if (cylinder->radius > 0.0)
		cylinder->radius *= (1 - RADIUS_FACTOR);
	update_scene(scene, CYLINDER_RADIUS);
}

static void	update_numpad(int key_code, t_scene *scene)
{
	if (!scene->index && key_code == NUMPAD_PLUS \
		&& scene->amb_light->ratio <= 1 - LIGHT_RATIO_FACTOR)
		scene->amb_light->ratio += LIGHT_RATIO_FACTOR;
	else if (!scene->index && key_code == NUMPAD_MINUS \
		&& scene->amb_light->ratio >= LIGHT_RATIO_FACTOR)
		scene->amb_light->ratio -= LIGHT_RATIO_FACTOR;
	else if (scene->index == 1 && key_code == NUMPAD_PLUS \
		&& scene->light->ratio <= 1 - LIGHT_RATIO_FACTOR)
		scene->light->ratio += LIGHT_RATIO_FACTOR;
	else if (scene->index == 1 && key_code == NUMPAD_MINUS \
		&& scene->light->ratio >= LIGHT_RATIO_FACTOR)
		scene->light->ratio -= LIGHT_RATIO_FACTOR;
	else if (scene->index && scene->objects[scene->index - 1]->type == CYLINDER)
		update_radius(key_code, scene);
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
	else if (key_code == NUMPAD_PLUS || key_code == NUMPAD_MINUS)
		update_numpad(key_code, scene);
	else if (key_code == KEY_TAB)
		change_mode(scene);
	else if (key_code == KEY_PAGE_UP)
		scene->index = (scene->index + 1) % (scene->nb_objects + 1);
	else if (key_code == KEY_PAGE_DOWN)
		scene->index = (scene->index - 1) % (scene->nb_objects + 1);
	print_window(scene);
	return (0);
}
