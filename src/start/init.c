/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 14:43:27 by ncotte            #+#    #+#             */
/*   Updated: 2023/02/16 23:21:39 by shalimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static int	init_img(t_image **image, void *mlx, int width, int height)
{
	*image = ft_calloc(1, sizeof (**image));
	if (!*image)
		return (print_error(ERROR, "Image allocation has failed"));
	(*image)->ptr = mlx_new_image(mlx, width, height);
	if (!(*image)->ptr)
		return (print_error(ERROR, "Image initialization has failed"));
	(*image)->addr = mlx_get_data_addr((*image)->ptr, &(*image)->bpp, \
		&(*image)->line_len, &(*image)->endian);
	if (!(*image)->addr)
		return (print_error(ERROR, "Image address not found"));
	(*image)->width = width;
	(*image)->height = height;
	return (SUCCESS);
}

static int	init_mlx(t_scene *scene)
{
	scene->mlx = mlx_init();
	if (!scene->mlx)
		return (print_error(ERROR, "MLX initialization has failed"));
	scene->window = mlx_new_window(scene->mlx, \
		scene->width, scene->height, "miniRT");
	if (!scene->window)
		return (print_error(ERROR, "Windows initialization has failed"));
	if (init_img(&scene->main_img, scene->mlx, scene->width, scene->height))
		return (ERROR);
	if (init_img(&scene->axis_img, scene->mlx, 100, 100))
		return (ERROR);
	print_window(scene, 1, scene->reflexions);
	return (SUCCESS);
}

int	init(int argc, char **argv, t_scene **scene)
{
	t_list	*objects;

	objects = NULL;
	*scene = ft_calloc(1, sizeof (**scene));
	if (!(*scene))
		return (print_error(ERROR, "Scene allocation failed"));
	(*scene)->nb_objects = read_file(argc, argv, &objects);
	if ((*scene)->nb_objects < 0)
		return (ERROR);
	if (parsing(*scene, &objects))
		return (ERROR);
	if (!(*scene)->width)
	{
		(*scene)->width = 1920;
		(*scene)->height = 1080;
	}
	update_scene(*scene, UPDATE_ALL);
	return (init_mlx(*scene));
}
