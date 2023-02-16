/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translation_cylinder.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 14:03:23 by ncotte            #+#    #+#             */
/*   Updated: 2023/02/12 14:03:25 by ncotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	translation_relative_cylinder(int key_code, t_scene *scene)
{
	t_point		vector;
	t_cylinder	*cylinder;

	cylinder = (t_cylinder *)scene->objects[scene->index - 1]->object;
	if (key_code == KEY_W)
		vector = scalar_multi(TRANSLATION_FACTOR, cylinder->direction);
	else if (key_code == KEY_S)
		vector = scalar_multi(-TRANSLATION_FACTOR, cylinder->direction);
	else
		return ;
	cylinder->coord = add_vectors(cylinder->coord, vector);
	update_scene(scene, CYLINDER_TRANSLATION);
}

void	translation_absolute_cylinder(t_scene *scene, t_point vector)
{
	t_cylinder	*cylinder;

	cylinder = (t_cylinder *)scene->objects[scene->index - 1]->object;
	cylinder->coord = add_vectors(cylinder->coord, vector);
	update_scene(scene, CYLINDER_TRANSLATION);
}
