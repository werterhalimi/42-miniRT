/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_window.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 14:39:19 by ncotte            #+#    #+#             */
/*   Updated: 2023/02/20 14:45:09 by shalimi          ###   ########.fr       */
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
		if (!isinf(tmp) && tmp * tmp <= phong.light_ray_dist_2 \
			&& tmp > 0.0 && scene->objects[i] != phong.object)
			return (YES);
	}
	return (NO);
}

static t_phong	set_phong(t_phong phong, t_point coord, t_color color)
{
	t_point	light_ray;

	phong.light_coord = coord;
	phong.light_color = color;
	light_ray = sub_vectors(phong.light_coord, phong.hit_point);
	phong.light_ray_dist_2 = norm_square(light_ray);
	phong.light_ray = unit_vector(light_ray);
	phong.dot_light_normal = dot_product(phong.light_ray, phong.normal);
	return (phong);
}

static void	print_object(t_phong *phong)
{
	if (phong->object->type <= TYPE_SPOT_LIGHT \
		|| phong->dot_light_normal <= 0.0)
		return ;
	phong_diffuse(phong, phong->dot_light_normal);
	phong_specular(phong, dot_product(phong->normal, \
		unit_vector(add_vectors(scalar_multi(-1.0, \
		phong->camera_ray), phong->light_ray))));
}

static unsigned int	find_color_pixel(t_scene *scene, \
						t_point pixel, unsigned int reflexions)
{
	t_phong			phong;
	t_list			*lst;
	t_spot_light	*sp;

	(void) reflexions;
	phong.camera_ray = unit_dist(pixel, scene->camera->coord);
	phong.object = find_intersect(scene, phong.camera_ray, \
		&phong.camera_ray_dist, NULL);
	if (!phong.object)
		return (0);
	phong.hit_point = add_vectors(scene->camera->coord, \
		scalar_multi(phong.camera_ray_dist, phong.camera_ray));
	phong.normal = phong.object->get_normal(phong.camera_ray, \
		phong.hit_point, phong.object->object);
	phong.object_color = phong.object->get_color(scene, phong.object, \
		phong.hit_point, phong.normal);
	phong_ambient(&phong, scene->amb_light);
	lst = scene->spot_lights;
	while (lst)
	{
		sp = (t_spot_light *)lst->content;
		phong = set_phong(phong, sp->coord, sp->ratio_color);
		if (!is_shadow(scene, phong) \
			&& dot_product(phong.light_ray, sp->direction) <= sp->cos_angle)
			print_object(&phong);
		lst = lst->next;
	}
	phong = set_phong(phong, scene->light->coord, scene->light->ratio_color);
	if (!is_shadow(scene, phong))
		print_object(&phong);
	return (color_trgb(phong.final_color));
}

void	print_window(t_scene *scene, int offset, unsigned int reflexions)
{
	int				x;
	int				y;
	t_point			tmp;
	t_point			pixel;
	unsigned int	color;

	x = -1;
	tmp = scene->window_corner;
	while (++x < scene->width)
	{
		y = -1;
		pixel = tmp;
		while (++y < scene->height)
		{
			if (!(x % offset) && !(y % offset))
				color = find_color_pixel(scene, pixel, reflexions);
			else if (x % offset && !(y % offset))
				color = get_pixel_color(scene, x - x % offset, y);
			put_pixel(scene, x, y, color);
			pixel = add_vectors(pixel, scene->camera->shift_y);
		}
		color = get_pixel_color(scene, x, 0);
		tmp = add_vectors(tmp, scene->camera->shift_x);
	}
	mlx_put_image_to_window(scene->mlx, scene->window, scene->image, 0, 0);
}
