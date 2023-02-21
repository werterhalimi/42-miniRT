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
	if (key_code != KEY_PAGE_UP && key_code != KEY_PAGE_DOWN \
		&& key_code != KEY_TAB && key_code != KEY_ESC)
		print_window(scene, 1, 1);
	return (0);
}

int	mouse_release(int mouse_code, int x, int y, t_scene *scene)
{
	(void) x;
	(void) y;
	if (mouse_code != LEFT_CLICK && mouse_code != RIGHT_CLICK)
		print_window(scene, 1, 1);
	return (0);
}
