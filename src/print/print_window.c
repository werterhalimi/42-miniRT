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

static void	write_progress(t_scene *scene, int offset, int u)
{
	static int	progress;
	static char	block[3];

	if (!progress)
	{
		progress = scene->main_img->width / 19;
		block[0] = (char)0xE2;
		block[1] = (char)0x96;
		block[2] = (char)0x88;
	}
	if (offset == 1 && !(u % progress))
		write(STDOUT_FILENO, block, 3);
}

static void	print_image(t_scene *scene, int offset, unsigned int reflexions)
{
	int				u;
	int				v;
	t_point			tmp;
	t_point			pixel;
	unsigned int	color;

	u = -1;
	tmp = scene->window_corner;
	while (++u < scene->main_img->width)
	{
		v = -1;
		pixel = tmp;
		write_progress(scene, offset, u);
		while (++v < scene->main_img->height)
		{
			if (!(u % offset) && !(v % offset))
				color = pixel_color(scene, pixel, reflexions);
			else if (u % offset && !(v % offset))
				color = get_pixel_color(scene->main_img, u - u % offset, v);
			put_pixel(scene->main_img, u, v, color);
			pixel = add_vectors(pixel, scene->camera->shift_y);
		}
		color = get_pixel_color(scene->main_img, u, 0);
		tmp = add_vectors(tmp, scene->camera->shift_x);
	}
}

void	print_window(t_scene *scene, int offset, unsigned int reflexions)
{
	if (offset == 1)
	{
		printf("Rendering :         |\n");
		write(STDOUT_FILENO, GREEN, ft_strlen(GREEN));
	}
	print_image(scene, offset, reflexions);
	write_progress(scene, offset, scene->main_img->width);
	if (offset == 1)
	{
		write(STDOUT_FILENO, RESET_COLOR, ft_strlen(RESET_COLOR));
		write(STDOUT_FILENO, "\n", 1);
	}
	mlx_put_image_to_window(scene->mlx, scene->window, \
		scene->main_img->ptr, 0, 0);
	if (scene->axis)
		print_graduation(scene);
}
