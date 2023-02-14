/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 13:15:34 by ncotte            #+#    #+#             */
/*   Updated: 2023/02/09 13:15:36 by ncotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static int	parse_fov(double *fov, char *item)
{
	if (!item)
		return (print_error(ERROR, "A CAMERA_FOV is missing"));
	if (str_to_double(item, fov, YES))
		return (print_error(ERROR, \
			"Invalid CAMERA_FOV format. Required: one double"));
	if (*fov < 0.0 || 180.0 < *fov)
		return (print_error(ERROR, \
			"The CAMERA_FOV must be included in [0.0; 180.0]"));
	*fov = *fov * M_PI / 180.0;
	return (SUCCESS);
}

int	parse_camera(t_scene *scene, t_list *current, t_object *object)
{
	char		*item;
	t_camera	*camera;

	(void)object;
	camera = scene->camera;
	if (camera)
		return (print_error(ERROR, \
			"There can be only one camera per scene"));
	camera = ft_calloc(1, sizeof (t_camera));
	if (!camera)
		return (print_error(ERROR, "Camera allocation failed"));
	item = next_item((char *)(current->content));
	if (parse_coord(&(camera->coord), item))
		return (ERROR);
	item = next_item(item);
	if (parse_vector(&(camera->front), item, YES))
		return (ERROR);
	item = next_item(item);
	if (parse_fov(&(camera->fov), item))
		return (ERROR);
	if (next_item(item))
		return (print_error(ERROR, "Too many items for camera"));
	camera->down = orthogonal_base(camera->front, &camera->right);
	scene->camera = camera;
	return (SUCCESS);
}
