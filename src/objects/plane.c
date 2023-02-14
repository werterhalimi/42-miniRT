/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 19:27:46 by ncotte            #+#    #+#             */
/*   Updated: 2023/01/29 19:27:48 by ncotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	update_plane(t_scene *scene, void *object, unsigned int flags)
{
	t_plane	*plane;

	if (!(flags & (CAMERA_TRANSLATION | PLANE_ALL)))
		return ;
	plane = (t_plane *)object;
	plane->value = dot_product(sub_vectors(plane->coord, \
		scene->camera->coord), plane->normal);
}
