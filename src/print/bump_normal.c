/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bump_normal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 18:12:36 by ncotte            #+#    #+#             */
/*   Updated: 2023/02/24 20:01:56 by shalimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_point	bump_normal(t_point normal, t_color color)
{
	t_point	perturbation;

	perturbation = (t_point){color.r, color.g, color.b};
	perturbation = scalar_multi(0.9, perturbation);
	return (unit_vector(add_vectors(perturbation, normal)));
}
