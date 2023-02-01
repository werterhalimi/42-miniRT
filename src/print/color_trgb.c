/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_trgb.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 14:48:45 by ncotte            #+#    #+#             */
/*   Updated: 2023/02/01 14:48:46 by ncotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	create_trgb(unsigned char t, unsigned char r, \
		unsigned char g, unsigned char b)
{
	return (*(int *)(unsigned char [4]){b, g, r, t});
}

unsigned char	color_get_t(int trgb)
{
	return (((unsigned char *)&trgb)[3]);
}

unsigned char	color_get_r(int trgb)
{
	return (((unsigned char *)&trgb)[2]);
}

unsigned char	color_get_g(int trgb)
{
	return (((unsigned char *)&trgb)[1]);
}

unsigned char	color_get_b(int trgb)
{
	return (((unsigned char *)&trgb)[0]);
}
