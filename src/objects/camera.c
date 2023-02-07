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

static void	info_camera(t_scene *scene)
{
	t_camera	*camera;
	t_point		tmp;

	camera = scene->camera;
	camera->fov = camera->fov * M_PI / 180.0;
	tmp = camera->front;
	if (tmp.x || tmp.y)
		tmp.z += 1.0;
	else if (tmp.z > 0)
		tmp.x -= 1.0;
	else
		tmp.x += 1.0;
	camera->right = unit_vector(cross_product(camera->front, tmp));
	camera->down = cross_product(camera->front, camera->right);
	camera->size_x = tan(camera->fov * 0.5);
	camera->pixel_size = 2.0 * camera->size_x / (double)(scene->width);
	camera->size_y = camera->size_x * (double)(scene->height) \
		/ (double)(scene->width);
	camera->shift_x = scalar_multi(camera->pixel_size, camera->right);
	camera->shift_y = scalar_multi(camera->pixel_size, camera->down);
	tmp = add_vectors(scalar_multi(camera->size_x, camera->right), \
		scalar_multi(camera->size_y, camera->down));
	scene->window_corner = sub_vectors(add_vectors(camera->coord, camera->front), tmp);
}

int	parse_camera(t_scene *scene, t_list *current, t_objects *object)
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
	scene->camera = camera;
	info_camera(scene);
	return (SUCCESS);
}
