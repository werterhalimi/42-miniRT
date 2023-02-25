/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_intersect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 13:47:47 by ncotte            #+#    #+#             */
/*   Updated: 2023/02/25 17:39:56 by shalimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	find_intersect(t_scene *scene, t_phong *phong)
{
	double	tmp;
	int		object_index;
	int		i;

	i = -1;
	object_index = 0;
	phong->object = NULL;
	phong->view_ray_dist = INFINITY;
	while (scene->objects[++i])
	{
		tmp = scene->objects[i]->intersect(phong->view_ray, \
			scene->objects[i]->object, phong->origin);
		if (!isinf(tmp) && tmp <= phong->view_ray_dist - FLT_EPSILON \
			&& tmp > 0.0 && (!phong->object || \
				scene->objects[i] != phong->object))
		{
			phong->object = scene->objects[i];
			phong->view_ray_dist = tmp;
			object_index = i + 1;
		}
	}
	return (object_index);
}
