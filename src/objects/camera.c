/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 19:27:20 by ncotte            #+#    #+#             */
/*   Updated: 2023/01/29 19:27:22 by ncotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static int	parse_fov(double *fov, char *item)
{
	if (!item)
		return (print_error(ERROR, "A FOV is missing"));
	if (str_to_d(item, fov, YES))
		return (print_error(ERROR, \
			"Invalid FOV format. Required: one double"));
	if (*fov < 0.0 || 180.0 < *fov)
		return (print_error(ERROR, \
			"The FOV must be included in [0.0; 180.0]"));
	return (SUCCESS);
}

int	parse_camera(t_scene *scene, t_list *current)
{
	char		*item;
	t_camera	*camera;

	camera = scene->camera;
	if (camera)
		return (print_error(ERROR, \
			"There can be only one camera per scene"));
	camera = ft_calloc(1, sizeof (t_camera));
	printf("parse_camera : camera : %p\n", camera); // TODO
	if (!camera)
		return (print_error(ERROR, "Camera allocation failed"));
	item = next_item((char *)(current->content));
	if (parse_coord(&(camera->coord), item))
		return (ERROR);
	item = next_item(item);
	if (parse_vector(&(camera->vector), item))
		return (ERROR);
	item = next_item(item);
	if (parse_fov(&(camera->fov), item))
		return (ERROR);
	if (next_item(item))
		return (print_error(ERROR, "Too many items for camera"));
	scene->camera = camera;
	return (SUCCESS);
}
