/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_window.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 14:39:19 by ncotte            #+#    #+#             */
/*   Updated: 2023/02/13 23:15:16 by shalimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static int	is_shadow(t_scene *scene, t_phong phong)
{
	double	tmp;
	int		i;

	i = 0;
	if (dot_product(phong.normal, phong.light_ray) <= 0.0)
		return (YES);
	phong.light_ray_dist_2 = norm_square(phong.light_ray);
	phong.light_ray = unit_vector(phong.light_ray);
	while (scene->objects[++i])
	{
		tmp = scene->objects[i]->intersect(phong.light_ray, \
			scene->objects[i]->object, &phong.hit_point);
		tmp *= tmp;
		if (!isinf(tmp) && tmp < phong.light_ray_dist_2 \
			&& scene->objects[i] != phong.object)
			return (YES);
	}
	return (NO);
}

static unsigned int	find_color_pixel(t_scene *scene, t_point ray)
{
	t_phong		phong;
//	double		intersect;
//	t_point		hit_point_to_light;
//	t_point		hit_point;
//	t_color		color;
//	t_object	*obj;

	phong.camera_ray = unit_vector(sub_vectors(ray, scene->camera->coord));
//	ray = unit_vector(sub_vectors(ray, scene->camera->coord));
	phong.object = find_intersect(scene, phong.camera_ray, \
		&phong.camera_ray_dist, NULL);
	if (!phong.object)
		return (0);
	phong.hit_point = add_vectors(scene->camera->coord, \
		scalar_multi(phong.camera_ray_dist, phong.camera_ray));
	phong.normal = phong.object->get_normal(phong.camera_ray, \
		phong.hit_point, phong.object->object);
	phong.light_ray = sub_vectors(scene->light->coord, phong.hit_point);
	phong.color = phong.object->get_color(scene, phong.object->object);
	if (is_shadow(scene, phong))
		return (phong_ambient(scene->amb_light, phong.color));
	return (phong.object->print(scene, phong.object->object, phong.hit_point, \
		unit_vector(phong.light_ray)));
}

void	print_window(t_scene *scene, int offset)
{
	int				x;
	int				y;
	t_point			tmp;
	t_point			ray;
	unsigned int	color;

	x = -1;
	tmp = scene->window_corner;
	while (++x < scene->width)
	{
		y = -1;
		ray = tmp;
		while (++y < scene->height)
		{
			if (!(x % offset) && !(y % offset))
				color = find_color_pixel(scene, ray);
			else if (x % offset && !(y % offset))
				color = get_pixel_color(scene, x - x % offset, y);
			put_pixel(scene, x, y, color);
			ray = add_vectors(ray, scene->camera->shift_y);
		}
		color = get_pixel_color(scene, x, 0);
		tmp = add_vectors(tmp, scene->camera->shift_x);
	}
	mlx_put_image_to_window(scene->mlx, scene->window, scene->image, 0, 0);
}
