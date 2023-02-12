/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translation_light.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 14:03:06 by ncotte            #+#    #+#             */
/*   Updated: 2023/02/12 14:03:08 by ncotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	translation_absolute_light(t_scene *scene, t_point vector)
{
	scene->light->coord = add_vectors(scene->light->coord, vector);
	update_scene(scene, LIGHT_TRANSLATION);
}
