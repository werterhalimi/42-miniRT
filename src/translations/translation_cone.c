/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translation_cone.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 17:31:58 by ncotte            #+#    #+#             */
/*   Updated: 2023/02/13 17:32:00 by ncotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	translation_relative_cone(int key_code, t_scene *scene)
{
	t_point	vector;
	t_cone	*cone;

	cone = (t_cone *)scene->objects[scene->index - 1]->object;
	if (key_code == KEY_W)
		vector = scalar_multi(TRANSLATION_FACTOR, cone->direction);
	else if (key_code == KEY_S)
		vector = scalar_multi(-TRANSLATION_FACTOR, cone->direction);
	else
		return ;
	cone->coord = add_vectors(cone->coord, vector);
	update_scene(scene, CONE_TRANSLATION);
}

void	translation_absolute_cone(t_scene *scene, t_point vector)
{
	t_cone	*cone;

	cone = (t_cone *)scene->objects[scene->index - 1]->object;
	cone->coord = add_vectors(cone->coord, vector);
	update_scene(scene, CONE_TRANSLATION);
}
