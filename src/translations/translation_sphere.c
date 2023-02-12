/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translation_sphere.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 14:03:14 by ncotte            #+#    #+#             */
/*   Updated: 2023/02/12 14:03:16 by ncotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	translation_absolute_sphere(t_scene *scene, t_point vector)
{
	t_sphere	*sphere;

	sphere = (t_sphere *)(scene->objects[scene->index - 1]->object);
	sphere->coord = add_vectors(sphere->coord, vector);
	update_scene(scene, SPHERE_TRANSLATION);
}
