/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_pixel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 14:38:58 by ncotte            #+#    #+#             */
/*   Updated: 2023/02/01 14:39:00 by ncotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	put_pixel(t_scene *scene, int x, int y, unsigned int color)
{
	char	*dst;

	dst = scene->addr + (y * scene->line_len + x * (scene->bpp / 8));
	*(unsigned int *)dst = color;
}
