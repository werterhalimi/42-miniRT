/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 15:01:11 by ncotte            #+#    #+#             */
/*   Updated: 2023/02/12 15:01:13 by ncotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static char	**init_type_name(void)
{
	char	**type_name;

	type_name = ft_calloc(NB_OBJECTS - 1, sizeof (*type_name));
	if (!type_name)
		return (NULL);
	type_name[TYPE_MAIN_LIGHT] = "main light";
	type_name[TYPE_SPHERE] = "sphere";
	type_name[TYPE_PLANE] = "plane";
	type_name[TYPE_CYLINDER] = "cylinder";
	type_name[TYPE_CONE] = "cone";
	type_name[TYPE_SPOT_LIGHT] = "spot light";
	return (type_name);
}

int	write_type(t_scene *scene)
{
	static char	**type_name;

	if (!type_name)
		type_name = init_type_name();
	if (!type_name)
		return (-1);
	if (!scene->index)
		return (printf("The camera is now selected\n"));
	return (printf("A %s is now selected\n", \
		type_name[scene->objects[scene->index - 1]->type]));
}

void	write_point(t_point point, char *name)
{
	printf("%s :\n", name);
	printf("x = %lf\n", point.x);
	printf("y = %lf\n", point.y);
	printf("z = %lf\n", point.z);
}

void	write_info(t_scene *scene)
{
	int	i;

	printf("SCENE :\n");
	printf("Mode : ");
	if (scene->mode)
		printf("absolute\n");
	else
		printf("relative\n");
	write_type(scene);
	printf("Camera :\n");
	write_point(scene->camera->coord, "Coordinates");
	write_point(scene->camera->front, "Orientation");
	printf("FOV = %lf\n", scene->camera->fov);
	printf("Ambient light ratio = %lf\n", scene->amb_light->ratio);
	write_point(scene->camera->right, "Right");
	write_point(scene->camera->down, "Down");
	write_point(scene->camera->shift_x, "Shift X");
	write_point(scene->camera->shift_y, "Shift Y");
	printf("Pixel size = %lf\n", scene->camera->pixel_size);
	printf("Size X = %lf\n", scene->camera->size_x);
	printf("Size Y = %lf\n", scene->camera->size_y);
	write_point(scene->window_corner, "Scene window corner");
	i = 0;
	while (scene->objects[i])
		printf("Object of type : %d\n", scene->objects[i++]->type);
}
