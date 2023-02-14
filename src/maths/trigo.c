/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trigo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 19:13:52 by ncotte            #+#    #+#             */
/*   Updated: 2023/02/10 19:13:54 by ncotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

double	cos_rot(void)
{
	static double	result;

	if (!result)
		result = __cospi(ROTATION_FACTOR);
	return (result);
}

double	cos_rot_1(void)
{
	static double	result;

	if (!result)
		result = 1.0 - cos_rot();
	return (result);
}

double	sin_rot(void)
{
	static double	result;

	if (!result)
		result = __sinpi(ROTATION_FACTOR);
	return (result);
}

double	n_sin_rot(void)
{
	static double	result;

	if (!result)
		result = sin_rot() * -1.0;
	return (result);
}

double	vector_angle(t_point a, t_point b)
{
	return (acos(dot_product(a, b)));
}
