/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 19:27:01 by ncotte            #+#    #+#             */
/*   Updated: 2023/01/29 19:27:05 by ncotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	update_light(t_scene *scene, void *object, unsigned int flags)
{
	t_light	*light;

	if (!(flags & (CAMERA_TRANSLATION | LIGHT_TRANSLATION)))
		return ;
	light = (t_light *)object;
	light->relative_coord = sub_vectors(light->coord, scene->camera->coord);
}
