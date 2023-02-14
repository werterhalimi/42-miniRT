/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 19:27:39 by ncotte            #+#    #+#             */
/*   Updated: 2023/01/29 19:27:40 by ncotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	radius_sphere(int mouse_code, t_scene *scene)
{
	t_sphere	*sphere;

	sphere = (t_sphere *)(scene->objects[scene->index - 1]->object);
	if (mouse_code == SCROLL_UP)
		sphere->radius *= (1 + RADIUS_FACTOR);
	else if (sphere->radius > 0.0)
		sphere->radius *= (1 - RADIUS_FACTOR);
	update_scene(scene, SPHERE_RADIUS);
}

void	update_sphere(t_scene *scene, void *object, unsigned int flags)
{
	t_sphere	*sp;

	if (!(flags & (CAMERA_TRANSLATION | SPHERE_ALL)))
		return ;
	sp = (t_sphere *)object;
	if (flags & (CAMERA_TRANSLATION | SPHERE_TRANSLATION))
		sp->relative_coord = sub_vectors(scene->camera->coord, sp->coord);
	if (flags & SPHERE_RADIUS)
		sp->radius_2 = sp->radius * sp->radius;
	sp->value = norm_square(sp->relative_coord) - sp->radius_2;
}
