/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_spot_light.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 11:50:21 by ncotte            #+#    #+#             */
/*   Updated: 2023/02/16 11:50:23 by ncotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "miniRT.h"

void	print_spot_light(t_phong *phong)
{
	(void) phong;
}

t_color	get_color_spot_light(t_scene *scene, void *object, \
	t_point hit_point, t_point normal)
{
	t_spot_light	*spot_light;

	(void) scene;
	(void) hit_point;
	(void) normal;
	spot_light = (t_spot_light *)object;
	return (spot_light->color);
}
