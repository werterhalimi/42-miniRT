/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_intersect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 13:47:47 by ncotte            #+#    #+#             */
/*   Updated: 2023/02/14 13:47:49 by ncotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_object	*find_intersect(t_scene *scene, t_point ray, \
				double *intersect, int *index)
{
	t_object	*object;
	double		first_intersect;
	double		tmp;
	int			i;

	i = -1;
	if (index)
		*index = 0;
	object = NULL;
	first_intersect = INFINITY;
	while (scene->objects[++i])
	{
		tmp = scene->objects[i]->intersect(ray, \
			scene->objects[i]->object, NULL);
		if (!isinf(tmp) && tmp < first_intersect)
		{
			object = scene->objects[i];
			first_intersect = tmp;
			if (index)
				*index = i + 1;
		}
	}
	if (intersect)
		*intersect = first_intersect;
	return (object);
}
