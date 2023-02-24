/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_trgb.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 14:48:45 by ncotte            #+#    #+#             */
/*   Updated: 2023/02/24 19:29:35 by shalimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_color	new_color(double r, double g, double b)
{
	t_color	color;

	color.r = r;
	color.g = g;
	color.b = b;
	return (color);
}

unsigned int	create_trgb(unsigned char t, unsigned char r, \
		unsigned char g, unsigned char b)
{
	return (*(unsigned int *)(unsigned char [4]){b, g, r, t});
}

unsigned int	color_trgb(t_color color)
{
	unsigned char	red;
	unsigned char	green;
	unsigned char	blue;

	red = (unsigned char)(color.r * 255.0);
	green = (unsigned char)(color.g * 255.0);
	blue = (unsigned char)(color.b * 255.0);
	return (*(unsigned int *)(unsigned char [4]){blue, green, red, 0});
}

t_color	sub_colors(t_color a, t_color b)
{
	return ((t_color){a.r - b.r, a.g - b.g, a.b - b.b});
}

t_color	add_colors(t_color a, t_color b)
{
	return ((t_color){a.r + b.r, a.g + b.g, a.b + b.b});
}
