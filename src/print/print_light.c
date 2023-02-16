/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 14:36:18 by ncotte            #+#    #+#             */
/*   Updated: 2023/02/16 02:20:10 by shalimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	print_light(t_phong *phong)
{
	(void) phong;
}

t_color	get_color_light(t_scene *scene, void *object)
{
	t_light	*light;

	(void)scene;
	light = (t_light *)object;
	return (light->color);
}
