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

int	is_sphere(t_point point, t_sphere sphere)
{
	if (norm_square(sub_vectors(point, sphere.coord)) \
		== sphere.radius * sphere.radius)
		return (YES);
	return (NO);
}

void	update_sphere(t_scene *scene, void *object, unsigned int flags)
{
	t_sphere	*sp;

	if (!(flags & (CAMERA_TRANSLATION | SPHERE_ALL)))
		return ;
	sp = (t_sphere *)object;
	if (flags & (CAMERA_TRANSLATION | SPHERE_TRANSLATION))
		sp->relative_coord = sub_vectors(scene->camera->coord, sp->coord);
	sp->value = norm_square(sp->relative_coord) - sp->radius * sp->radius;
}
