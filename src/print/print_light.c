/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 14:36:18 by ncotte            #+#    #+#             */
/*   Updated: 2023/02/12 14:36:20 by ncotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

double	intersect_light(t_point ray, void *object)
{
	t_light	*light;
	double	t;

	light = (t_light *)object;
	t = light->relative_coord.x / ray.x;
	if (is_null(add_vectors(scalar_multi(t, ray), \
		light->relative_coord)) && t >= 0.0)
		return (t);
	return (INFINITY);
}

unsigned int	get_color_light(t_scene *scene, void *object)
{
	t_light	*light;

	(void)scene;
	light = (t_light *)object;
	return (color_trgb(light->color));
}
