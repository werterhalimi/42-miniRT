/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   amb_light.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 19:27:30 by ncotte            #+#    #+#             */
/*   Updated: 2023/01/29 19:27:32 by ncotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	ratio_amb_light(int key_code, t_scene *scene)
{
	if (key_code == NUMPAD_PLUS \
		&& scene->amb_light->ratio <= 1.0 - LIGHT_RATIO_FACTOR + FLT_EPSILON)
		scene->amb_light->ratio += LIGHT_RATIO_FACTOR;
	else if (key_code == NUMPAD_MINUS \
		&& scene->amb_light->ratio >= LIGHT_RATIO_FACTOR - FLT_EPSILON)
		scene->amb_light->ratio -= LIGHT_RATIO_FACTOR;
}
