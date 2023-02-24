/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 17:29:26 by ncotte            #+#    #+#             */
/*   Updated: 2023/02/01 17:29:48 by ncotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	quit(t_scene *scene)
{
	if (scene->main_img)
		mlx_destroy_image(scene->mlx, scene->main_img->ptr);
	if (scene->axis_img)
		mlx_destroy_image(scene->mlx, scene->axis_img->ptr);
	if (scene->window)
		mlx_destroy_window(scene->mlx, scene->window);
	ft_flush();
	exit(SUCCESS);
}
