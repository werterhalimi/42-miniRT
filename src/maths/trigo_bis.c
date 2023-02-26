/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trigo_bis.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 16:59:20 by ncotte            #+#    #+#             */
/*   Updated: 2023/02/24 16:59:22 by ncotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

double	cos_rot_1(void)
{
	static double	result;

	if (!result)
		result = 1.0 - cos_rot();
	return (result);
}

double	n_sin_rot(void)
{
	static double	result;

	if (!result)
		result = sin_rot() * -1.0;
	return (result);
}

double	get_latitude(t_point vector, t_point front, double radius)
{
	double	latitude;
	double	delta_z;

	delta_z = dot_product(vector, front);
	latitude = asin(delta_z / radius);
	return (latitude);
}

double	get_longitude(t_point vector, t_point right, t_point down)
{
	double	longitude;
	double	delta_x;
	double	delta_y;

	delta_x = dot_product(vector, right);
	delta_y = dot_product(vector, down);
	if (delta_x == 0.0)
		longitude = M_PI_2;
	else
		longitude = atan(delta_y / delta_x);
	if (delta_x < 0.0)
		longitude += M_PI;
	return (longitude);
}
