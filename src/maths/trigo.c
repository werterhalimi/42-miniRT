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

#ifdef __APPLE__

double	cos_rot(void)
{
	static double	result;

	if (!result)
		result = __cospi(ROTATION_FACTOR);
	return (result);
}

double	sin_rot(void)
{
	static double	result;

	if (!result)
		result = __sinpi(ROTATION_FACTOR);
	return (result);
}

#else

double	cos_rot(void)
{
	static double	result;

	if (!result)
		result = cos(ROTATION_FACTOR * M_PI);
	return (result);
}

double	sin_rot(void)
{
	static double	result;

	if (!result)
		result = sin(ROTATION_FACTOR * M_PI);
	return (result);
}

#endif
