/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 22:18:57 by shalimi           #+#    #+#             */
/*   Updated: 2023/02/13 22:35:28 by shalimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

unsigned int	phong_ambient(t_amb_light *amb_light, t_color base)
{
	return (create_trgb(0, \
		(amb_light->color.r + base.r) / 255 * amb_light->ratio, \
		(amb_light->color.g + base.g) / 255 * amb_light->ratio, \
		(amb_light->color.b + base.b) / 255 * amb_light->ratio));
}

unsigned int	phong_color(t_scene *scene, t_color base, double dot)
{
	double	r;
	double	g;
	double	b;

	r = (scene->amb_light->color.r + base.r) / 255 * scene->amb_light->ratio;
	g = (scene->amb_light->color.g + base.g) / 255 * scene->amb_light->ratio;
	b = (scene->amb_light->color.b + base.b) / 255 * scene->amb_light->ratio;
	r += (scene->light->color.r * base.r * dot / 255) * scene->light->ratio;
	g += (scene->light->color.g * base.g * dot / 255) * scene->light->ratio;
	b += (scene->light->color.b * base.b * dot / 255) * scene->light->ratio;
	// r+= specular * (scene->light0>color.r - base.r)
	return (create_trgb(0, r, g, b));
}
