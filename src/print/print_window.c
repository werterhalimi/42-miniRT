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

void	print_window(t_scene *scene)
{
	int				x;
	int				y;
	int				total;
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;

	x = -1;
	total = scene->width + scene->height;
	while (++x < scene->width)
	{
		y = -1;
		while (++y < scene->height)
		{
			r = scene->amb_light->color.r * (x + y) / total;
			g = scene->amb_light->color.g * (x + y) / total;
			b = scene->amb_light->color.b * (x + y) / total;
			put_pixel(scene, x, y, create_trgb(0, r, g, b));
		}
	}
	mlx_put_image_to_window(scene->mlx, scene->window, scene->image, 0, 0);
}
