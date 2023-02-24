/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 17:58:50 by ncotte            #+#    #+#             */
/*   Updated: 2023/02/24 17:58:51 by ncotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static int	is_shadow(t_scene *scene, t_phong phong)
{
	double	tmp;
	int		i;

	i = 0;
	if (phong.dot_light_normal <= 0.0)
		return (YES);
	while (scene->objects[++i])
	{
		tmp = scene->objects[i]->intersect(phong.light_ray, \
			scene->objects[i]->object, &phong.hit_point);
		if (!isinf(tmp) && tmp * tmp <= phong.light_ray_dist_2 - FLT_EPSILON \
			&& tmp > 0.0 && scene->objects[i] != phong.object)
			return (YES);
	}
	return (NO);
}

static int	ray_color(t_scene *scene, t_phong *phong, t_point origin)
{
	t_list			*lst;
	t_spot_light	*sp;

	find_intersect(scene, phong);
	if (!phong->object)
		return (NO);
	init_phong(scene, phong, origin);
	lst = scene->spot_lights;
	while (lst)
	{
		sp = (t_spot_light *)lst->content;
		set_phong(phong, sp->coord, sp->ratio_color);
		if (!is_shadow(scene, *phong) \
			&& dot_product(phong->light_ray, sp->direction) <= sp->cos_angle)
			phong_object(phong);
		lst = lst->next;
	}
	set_phong(phong, scene->light->coord, scene->light->ratio_color);
	if (!is_shadow(scene, *phong))
		phong_object(phong);
	return (YES);
}

unsigned int	pixel_color(t_scene *scene, t_point pixel, \
					unsigned int reflexions)
{
	t_phong			phong;
	t_point			origin;
	unsigned int	i;

	i = 0;
	origin = scene->camera->coord;
	phong.final_color = new_color(0.0, 0.0, 0.0);
	phong.view_ray = unit_dist(pixel, scene->camera->coord);
	phong.origin = NULL;
	while (++i)
	{
		ray_color(scene, &phong, origin);
		if (i > reflexions || !phong.object || phong.object->reflectance == 0.0)
			break ;
		phong.view_ray = reflection(phong.view_ray, phong.normal);
		if (i == 1)
		{
			phong.origin = ft_calloc(1, sizeof (*phong.origin));
			if (!phong.origin)
				return (color_trgb(phong.final_color));
		}
		*phong.origin = phong.hit_point;
		origin = phong.hit_point;
	}
	return (color_trgb(phong.final_color));
}
