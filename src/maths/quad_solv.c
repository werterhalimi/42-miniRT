/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quad_solv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 11:32:31 by ncotte            #+#    #+#             */
/*   Updated: 2023/02/06 11:32:33 by ncotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

double	quad_solv(double a, double b, double c, double *x)
{
	double	det;
	double	sqrt_det;
	double	div;

	div = 2.0 * a;
	det = b * b - 4 * a * c;
	if (det > 0.0)
	{
		sqrt_det = sqrt(det);
		*x = (-b + sqrt_det) / div;
		return ((-b - sqrt_det) / div);
	}
	if (det < 0.0)
		*x = NAN;
	else
		*x = -b / div;
	return (*x);
}
