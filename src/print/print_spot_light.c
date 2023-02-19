/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_spot_light.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 11:50:21 by ncotte            #+#    #+#             */
/*   Updated: 2023/02/17 21:04:02 by shalimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_color	get_color_spot_light(t_scene *scene, t_object *object, \
	t_point hit_point, t_point normal)
{
	t_spot_light	*spot_light;

	(void) scene;
	(void) hit_point;
	(void) normal;
	spot_light = (t_spot_light *)object->object;
	return (spot_light->color);
}
