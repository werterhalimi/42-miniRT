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
		tmp *= tmp;
		if (!isinf(tmp) && tmp * tmp <= phong.light_ray_dist_2 \
			&& tmp > 0.0 && scene->objects[i] != phong.object)
			return (YES);
	}
	return (NO);
}

static t_phong	set_phong(t_phong phong, t_point coord, \
					double ratio, t_color color)
{
	t_point	light_ray;

	phong.light_coord = coord;
	phong.light_ratio = ratio;
	phong.light_color = color;
	light_ray = sub_vectors(phong.light_coord, phong.hit_point);
	phong.light_ray_dist_2 = norm_square(light_ray);
	phong.light_ray = unit_vector(light_ray);
	phong.dot_light_normal = dot_product(phong.light_ray, phong.normal);
	return (phong);
}

static void	print_object(t_phong *phong)
{
	t_point	h;

	if (phong->object->type <= TYPE_SPOT_LIGHT || phong->dot_light_normal <= 0.0)
		return ;
	h = add_vectors(scalar_multi(-1.0, phong->camera_ray), phong->light_ray);
	h = unit_vector(h);
	phong_diffuse(phong, phong->dot_light_normal);
	phong_specular(phong, pow(dot_product(phong->normal, h), \
		phong->object->specular));
}

static unsigned int	find_color_pixel(t_scene *scene, t_point pixel)
{
	t_phong			phong;
	t_list			*lst;
	t_spot_light	*sp;

	phong.camera_ray = unit_dist(pixel, scene->camera->coord);
	phong.object = find_intersect(scene, phong.camera_ray, \
		&phong.camera_ray_dist, NULL);
	if (!phong.object)
		return (0);
	phong_ambient(scene->amb_light, phong.color, phong.rgb);
	phong.hit_point = add_vectors(scene->camera->coord, \
		scalar_multi(phong.camera_ray_dist, phong.camera_ray));
	phong.normal = phong.object->get_normal(phong.camera_ray, \
		phong.hit_point, phong.object->object);
	phong.color = phong.object->get_color(scene, phong.object, \
		phong.hit_point, phong.normal);
	lst = scene->spot_lights;
	while (lst)
	{
		sp = (t_spot_light *)lst->content;
		phong = set_phong(phong, sp->coord, sp->ratio, sp->color);
		if (!is_shadow(scene, phong) \
			&& dot_product(phong.light_ray, sp->direction) <= sp->cos_angle)
			print_object(&phong);
		//	phong.object->print(&phong);
		// phong.object->object, phong.hit_point, 
	//	unit_vector(phong.light_ray)));
		lst = lst->next;
	}
	phong = set_phong(phong, scene->light->coord, \
		scene->light->ratio, scene->light->color);
	if (!is_shadow(scene, phong))
		print_object(&phong);
	//	phong.object->print(&phong);// phong.object->object, phong.hit_point, 
		//	unit_vector(phong.light_ray)));
/*	if (phong.rgb[0] > 255)
		phong.rgb[0] = 255;
	if (phong.rgb[1] > 255)
		phong.rgb[1] = 255;
	if (phong.rgb[2] > 255)
		phong.rgb[2] = 255;
	*/
	return (create_trgb(0, phong.rgb[0], phong.rgb[1], phong.rgb[2]));
}

void	print_window(t_scene *scene, int offset)
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
				color = find_color_pixel(scene, pixel);
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
