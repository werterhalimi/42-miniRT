/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quake.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 16:48:50 by ncotte            #+#    #+#             */
/*   Updated: 2023/02/02 16:48:52 by ncotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

double	inv_sqrt(double d)
{
	long	l;
	double	y;

	y = d;
	d *= 0.5;
	l = *(long *)&y;
	l = 0x5FE6EB50C7B537A9 - (l >> 1);
	y = *(double *)&l;
	y = y * (1.5 - (d * y * y));
	y = y * (1.5 - (d * y * y));
	y = y * (1.5 - (d * y * y));
	return (y);
}

t_point	unit_vector(t_point vector)
{
	return (scalar_multi(inv_sqrt(norm_square(vector)), vector));
}
