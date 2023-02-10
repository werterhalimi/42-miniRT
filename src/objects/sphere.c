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

double	intersect_sphere(t_point ray, void *object)
{
	t_sphere	*sphere;
	double		t1;
	double		t2;

	sphere = (t_sphere *)object;
	t1 = quad_solv(1, 2.0 * dot_product(ray, \
		sphere->relative_coord), sphere->value, &t2);
	if (!isnan(t1) && t1 < t2 && t1 >= 0.0)
		return (t1);
	if (!isnan(t2) && t2 >= 0.0)
		return (t2);
	return (INFINITY);
}

void	translation_absolute_sphere(t_scene *scene, t_point vector)
{
	t_sphere	*sphere;

	sphere = (t_sphere *)(scene->objects[scene->index - 1]->object);
	sphere->coord = add_vectors(sphere->coord, vector);
	update_scene(scene, SPHERE_TRANSLATION);
}

unsigned int	get_color_sphere(t_scene *scene, void *object)
{
	t_sphere	*sphere;

	(void)scene;
	sphere = (t_sphere *)object;
	return (color_trgb(sphere->color));
}
