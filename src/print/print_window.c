/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_window.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 14:39:19 by ncotte            #+#    #+#             */
/*   Updated: 2023/02/22 17:36:35 by shalimi          ###   ########.fr       */
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

static void	set_phong(t_phong *phong, t_point coord, t_color color)
{
	t_point	light_ray;

	phong->light_coord = coord;
	phong->light_color = color;
	light_ray = sub_vectors(phong->light_coord, phong->hit_point);
	phong->light_ray_dist_2 = norm_square(light_ray);
	phong->light_ray = unit_vector(light_ray);
	phong->dot_light_normal = dot_product(phong->light_ray, phong->normal);
}

static void	print_object(t_phong *phong)
{
	if (phong->object->type <= TYPE_SPOT_LIGHT \
		|| phong->dot_light_normal <= 0.0)
		return ;
	phong_diffuse(phong, phong->dot_light_normal);
	phong_specular(phong, dot_product(phong->normal, \
		unit_vector(add_vectors(scalar_multi(-1.0, \
		phong->view_ray), phong->light_ray))));
}

static int	ray_color(t_scene *scene, t_phong *phong, t_point origin)
{
	t_list			*lst;
	t_spot_light	*sp;

	find_intersect(scene, phong);
	if (!phong->object)
		return (NO);
	phong->hit_point = add_vectors(origin, \
		scalar_multi(phong->view_ray_dist, phong->view_ray));
	phong->normal = phong->object->get_normal(phong->view_ray, \
		phong->hit_point, phong->object->object, phong->object->normal_map);
	phong->object_color = phong->object->get_color(scene, phong->object, \
		phong->hit_point, phong->normal);
	phong_ambient(phong, scene->amb_light);
	lst = scene->spot_lights;
	while (lst)
	{
		sp = (t_spot_light *)lst->content;
		set_phong(phong, sp->coord, sp->ratio_color);
		if (!is_shadow(scene, *phong) \
			&& dot_product(phong->light_ray, sp->direction) <= sp->cos_angle)
			print_object(phong);
		lst = lst->next;
	}
	set_phong(phong, scene->light->coord, scene->light->ratio_color);
	if (!is_shadow(scene, *phong))
		print_object(phong);
	return (YES);
}

static unsigned int	find_color_pixel(t_scene *scene, \
						t_point pixel, unsigned int reflexions)
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

void	print_window(t_scene *scene, int offset, unsigned int reflexions)
{
	int				x;
	int				y;
	int 			progress;
	t_point			tmp;
	t_point			pixel;
	unsigned int	color;
	char happy[] = { 0xE2, 0x96, 0x88 };  /* U+2588 */

	x = -1;
	tmp = scene->window_corner;
	progress = scene->width / 20;
	if (offset == 1)
		printf("Rendering : \n");
	while (++x < scene->width)
	{
		y = -1;
		pixel = tmp;
		if (offset == 1 && !(x % progress))
			write(STDOUT_FILENO, happy, 3);
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
	if (offset == 1)
		printf("\n");
	mlx_put_image_to_window(scene->mlx, scene->window, scene->image, 0, 0);
}
