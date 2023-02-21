/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 22:18:57 by shalimi           #+#    #+#             */
/*   Updated: 2023/02/17 21:17:42 by shalimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	phong_ambient(t_phong *phong, t_amb_light *amb_light)
{
	phong->final_color.r = fmin(amb_light->ratio_color.r \
		* phong->object_color.r, 1.0);
	phong->final_color.g = fmin(amb_light->ratio_color.g \
		* phong->object_color.g, 1.0);
	phong->final_color.b = fmin(amb_light->ratio_color.b \
		* phong->object_color.b, 1.0);
}

void	phong_diffuse(t_phong *phong, double dot)
{
	if (dot <= 0.0)
		return ;
	phong->final_color.r = fmin(phong->light_color.r \
		* phong->object_color.r * dot + phong->final_color.r, 1.0);
	phong->final_color.g = fmin(phong->light_color.g \
		* phong->object_color.g * dot + phong->final_color.g, 1.0);
	phong->final_color.b = fmin(phong->light_color.b \
		* phong->object_color.b * dot + phong->final_color.b, 1.0);
}

void	phong_specular(t_phong *phong, double dot)
{
	double	specular;

	if (dot <= 0.0 || phong->object->specular == 0.0)
		return ;
	specular = pow(dot, phong->object->specular);
	phong->final_color.r = fmin(phong->light_color.r \
		* specular + phong->final_color.r, 1.0);
	phong->final_color.g = fmin(phong->light_color.g \
		* specular + phong->final_color.g, 1.0);
	phong->final_color.b = fmin(phong->light_color.b \
		* specular + phong->final_color.b, 1.0);
}
