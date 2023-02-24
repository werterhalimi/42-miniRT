/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 13:51:29 by ncotte            #+#    #+#             */
/*   Updated: 2023/02/09 13:51:31 by ncotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

unsigned int	get_pixel_color(t_image *image, int x, int y)
{
	return (*(unsigned int *)(image->addr + (y * image->line_len \
		+ x * (image->bpp / 8))));
}

unsigned char	color_get_t(unsigned int trgb)
{
	return (((unsigned char *)&trgb)[3]);
}

unsigned char	color_get_r(unsigned int trgb)
{
	return (((unsigned char *)&trgb)[2]);
}

unsigned char	color_get_g(unsigned int trgb)
{
	return (((unsigned char *)&trgb)[1]);
}

unsigned char	color_get_b(unsigned int trgb)
{
	return (((unsigned char *)&trgb)[0]);
}
