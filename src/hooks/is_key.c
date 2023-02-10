/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_key.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 14:29:52 by ncotte            #+#    #+#             */
/*   Updated: 2023/02/10 14:29:54 by ncotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	is_key_translation(int key_code)
{
	return (key_code == KEY_W || key_code == KEY_S || key_code == KEY_A \
		|| key_code == KEY_D || key_code == KEY_E || key_code == KEY_Q);
}

int	is_key_rotation(int key_code)
{
	return (key_code == NUMPAD_2 || key_code == NUMPAD_4 \
		|| key_code == NUMPAD_6 || key_code == NUMPAD_7 \
		|| key_code == NUMPAD_8 || key_code == NUMPAD_9);
}
