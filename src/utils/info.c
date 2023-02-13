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
	type_name[MAIN_LIGHT] = "main light";
	type_name[SPHERE] = "sphere";
	type_name[PLANE] = "plane";
	type_name[CYLINDER] = "cylinder";
	type_name[CONE] = "cone";
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
}
