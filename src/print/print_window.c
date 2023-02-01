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
	int	a;
	int	b;

	a = -1;
	while (++a < scene->width)
	{
		b = -1;
		while (++b < scene->height)
			put_pixel(scene, a, b, create_trgb(127, 255, 255, 255));
	}
	mlx_put_image_to_window(scene->mlx, scene->win, scene->img, 0, 0);
}
