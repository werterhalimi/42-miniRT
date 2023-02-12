/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   release.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 16:59:53 by ncotte            #+#    #+#             */
/*   Updated: 2023/02/12 16:59:55 by ncotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	key_release(int key_code, t_scene *scene)
{
	(void) key_code;
	print_window(scene, 1);
	return (0);
}

int	mouse_release(int mouse_code, int x, int y, t_scene *scene)
{
	(void) mouse_code;
	(void) x;
	(void) y;
	print_window(scene, 1);
	return (0);
}
