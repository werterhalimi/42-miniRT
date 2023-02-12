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
	printf("%sGOODBYE!%s\n", BOLD_YELLOW, RESET_COLOR);
	if (scene->image)
		mlx_destroy_image(scene->mlx, scene->image);
	if (scene->window)
		mlx_destroy_window(scene->mlx, scene->window);
	ft_flush();
	exit(SUCCESS);
}
