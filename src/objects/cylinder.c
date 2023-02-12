/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 19:28:07 by ncotte            #+#    #+#             */
/*   Updated: 2023/01/29 19:28:08 by ncotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	is_cylinder(t_point point, t_cylinder cylinder)
{
	t_point	vector_p;
	t_point	proj_p;
	double	height_p;
	double	radius_p;

	vector_p = sub_vectors(point, cylinder.coord);
	proj_p = scalar_multi(dot_product(vector_p, \
		cylinder.direction), cylinder.direction);
	height_p = norm_square(proj_p);
	radius_p = norm_square(sub_vectors(vector_p, proj_p));
	if ((height_p == cylinder.semi_height_square \
		&& radius_p < cylinder.radius_square) \
		|| (height_p < cylinder.semi_height_square \
		&& radius_p == cylinder.radius_square))
		return (YES);
	return (NO);
}

static void	update_top_down(t_cylinder *cy, t_point eye, unsigned int flags)
{
	if (flags & CYLINDER_ALL)
	{
		cy->center_top = add_vectors(cy->coord, cy->vector_semi_height);
		cy->center_down = add_vectors(cy->coord, \
			scalar_multi(-cy->semi_height, cy->direction));
	}
	cy->value_semi_height = dot_product(cy->relative_coord, \
		cy->vector_semi_height);
	cy->relative_center_top = sub_vectors(cy->center_top, eye);
	cy->relative_center_down = sub_vectors(cy->center_down, eye);
	cy->value_top = dot_product(cy->relative_center_top, cy->direction);
	cy->value_down = dot_product(cy->relative_center_down, cy->direction);
}

void	update_cylinder(t_scene *scene, void *object, unsigned int flags)
{
	t_cylinder	*cy;

	if (!(flags & (CAMERA_TRANSLATION | CYLINDER_ALL)))
		return ;
	cy = (t_cylinder *)object;
	if (flags & CYLINDER_RADIUS)
		cy->radius_square = cy->radius * cy->radius;
	if (flags & CYLINDER_HEIGHT)
		cy->semi_height_square = cy->semi_height * cy->semi_height;
	if (flags & (CYLINDER_HEIGHT | CYLINDER_ROTATION))
		cy->vector_semi_height = scalar_multi(cy->semi_height, cy->direction);
	if (flags & (CYLINDER_TRANSLATION | CAMERA_TRANSLATION))
		cy->relative_coord = sub_vectors(scene->camera->coord, cy->coord);
	if (flags & (CYLINDER_ROTATION | CYLINDER_TRANSLATION | CAMERA_TRANSLATION))
		cy->value = dot_product(cy->relative_coord, cy->direction);
	if (flags == UPDATE_ALL \
		|| flags & ((CYLINDER_ALL & ~CYLINDER_RADIUS) | CAMERA_TRANSLATION))
		update_top_down(cy, scene->camera->coord, flags);
	if (flags == UPDATE_ALL \
		|| flags & ((CYLINDER_ALL & ~CYLINDER_HEIGHT) | CAMERA_TRANSLATION))
		cy->value_quad = norm_square(cy->relative_coord) \
			- cy->value * cy->value - cy->radius_square;
}
