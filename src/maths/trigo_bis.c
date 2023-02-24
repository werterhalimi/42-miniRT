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
