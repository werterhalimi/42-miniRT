/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 14:36:18 by ncotte            #+#    #+#             */
/*   Updated: 2023/02/17 21:04:02 by shalimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_color	get_color_light(t_scene *scene, t_object *object, \
	t_point hit_point, t_point normal)
{
	t_light	*light;

	(void) scene;
	(void) hit_point;
	(void) normal;
	light = (t_light *)object->object;
	return (light->real_color);
}
