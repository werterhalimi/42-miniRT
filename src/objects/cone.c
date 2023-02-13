/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 16:30:54 by ncotte            #+#    #+#             */
/*   Updated: 2023/02/13 16:30:56 by ncotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	update_base(t_cone *co, t_point eye, unsigned int flags)
{
	if (flags & CONE_ALL)
		co->center_base = add_vectors(co->coord, co->vector_height);
	co->value_height = dot_product(co->relative_coord, \
		co->vector_height);
	co->relative_center_base = sub_vectors(co->center_base, eye);
	co->value_base = dot_product(co->relative_center_base, co->direction);
}

void	update_cone(t_scene *scene, void *object, unsigned int flags)
{
	t_cone	*co;

	if (!(flags & (CAMERA_TRANSLATION | CONE_ALL)))
		return ;
	co = (t_cone *)object;
	if (flags & CONE_RADIUS)
		co->radius_2 = co->radius * co->radius;
	if (flags & CONE_HEIGHT)
		co->height_2 = co->height * co->height;
	if (flags & (CONE_RADIUS | CONE_HEIGHT))
		co->ratio = co->radius_2 / co->height_2 + 1.0;
	if (flags & (CONE_HEIGHT | CONE_ROTATION))
		co->vector_height = scalar_multi(co->height, co->direction);
	if (flags & (CONE_TRANSLATION | CAMERA_TRANSLATION))
		co->relative_coord = sub_vectors(scene->camera->coord, co->coord);
	if (flags & (CONE_ROTATION | CONE_TRANSLATION | CAMERA_TRANSLATION))
		co->value = dot_product(co->relative_coord, co->direction);
	if (flags == UPDATE_ALL \
		|| flags & ((CONE_ALL & ~CONE_RADIUS) | CAMERA_TRANSLATION))
		update_base(co, scene->camera->coord, flags);
	if (flags == UPDATE_ALL \
		|| flags & ((CONE_ALL & ~CONE_HEIGHT) | CAMERA_TRANSLATION))
		co->value_quad = norm_square(co->relative_coord) \
			- co->ratio * co->value * co->value;
}

unsigned int	get_color_cone(t_scene *scene, void *object)
{
	t_cone	*cone;

	(void)scene;
	cone = (t_cone *)object;
	return (color_trgb(cone->color));
}
