/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bump_normal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 18:12:36 by ncotte            #+#    #+#             */
/*   Updated: 2023/02/25 19:16:12 by shalimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_point	bump_normal(double relief, t_point normal, t_color color)
{
	t_point	perturbation;

	perturbation = (t_point){color.r, color.g, color.b};
	return (unit_vector(add_vectors(scalar_multi(relief, \
		perturbation), normal)));
}
