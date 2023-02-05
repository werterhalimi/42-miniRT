/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_window.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 14:39:19 by ncotte            #+#    #+#             */
/*   Updated: 2023/02/01 14:39:21 by ncotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	init_static(double (*fct_array[])(t_scene *, t_point, int))
{
	fct_array[MAIN_LIGHT] = &intersect_light;
	fct_array[SPHERE] = &intersect_sphere;
	fct_array[PLANE] = &intersect_plane;
	fct_array[CYLINDER] = &intersect_cylinder;
}

static unsigned int	color_object(t_scene *scene, int i, int j)
{

}

static int	find_color_pixel(t_scene *scene, unsigned int *color, t_point ray)
{
	static unsigned int	(*color_ray)(t_scene *, int);
	static double		(*fct_array[NB_OBJECTS - 2])(t_scene *, t_point, int);
	double				first_intersect;
	double				tmp;
	int					i;

	if (!(*fct_array))
		init_static(fct_array);
	i = -1;
	*color = 0;
	first_intersect = INFINITY;
	while ((scene->objects)[++i])
	{
		j = 0;
		while ((scene->objects_type)[i] != j)
			j++;
		tmp = fct_array[j](scene, ray, i);
		if (tmp < first_intersect)
		{
			first_intersect = tmp;
			*color = color_object(scene, i);
		}
	}
	return (SUCCESS);
}

int	print_window(t_scene *scene)
{
	int				x;
	int				y;
	unsigned int	color;
	t_point			tmp;
	t_point			ray;

	x = -1;
	tmp = scene->window_corner;
	while (++x < scene->width)
	{
		y = -1;
		ray = tmp;
		while (++y < scene->height)
		{
			if (find_color_pixel(scene, &color, unit_vector(ray)))
				return (ERROR);
			put_pixel(scene, x, y, color);
			ray = add_vectors(ray, scene->camera->shift_y);
		}
		tmp = add_vectors(tmp, scene->camera->shift_x);
	}
	mlx_put_image_to_window(scene->mlx, scene->window, scene->image, 0, 0);
	return (SUCCESS);
}
