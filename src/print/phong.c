/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 22:18:57 by shalimi           #+#    #+#             */
/*   Updated: 2023/02/17 18:44:02 by shalimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	phong_ambient(t_amb_light *amb_light, t_color base, double *rgb)
{
	rgb[0] = (double)amb_light->color.r * (double)base.r / 255 \
		* amb_light->ratio;
	rgb[1] = (double)amb_light->color.g * (double)base.g / 255 \
		* amb_light->ratio;
	rgb[2] = (double)amb_light->color.b * (double)base.b / 255 \
		* amb_light->ratio;
}

void	phong_diffuse(t_phong *phong, double dot)
{
	double	*rgb;

	rgb = phong->rgb;
	rgb[0] += phong->light_color.r * phong->color.r * dot / 255 \
		* phong->light_ratio;
	rgb[1] += phong->light_color.g * phong->color.g * dot / 255 \
		* phong->light_ratio;
	rgb[2] += phong->light_color.b * phong->color.b * dot / 255 \
		* phong->light_ratio;
	// r+= specular * (scene->light0>color.r - base.r)
}


void	phong_specular(t_phong *phong, double specular)
{
	double	*rgb;

	rgb = phong->rgb;
	rgb[0] += fmax(0, phong->light_ratio * specular * (phong->light_color.r - rgb[0]));
	rgb[1] += fmax(0, phong->light_ratio * specular * (phong->light_color.g - rgb[1]));
	rgb[2] += fmax(0, phong->light_ratio * specular * (phong->light_color.b - rgb[2]));
	// r+= specular * (scene->light0>color.r - base.r)
}
