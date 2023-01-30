/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 17:02:55 by ncotte            #+#    #+#             */
/*   Updated: 2023/01/29 17:02:58 by ncotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	print_error(int error_code, char *error_msg)
{
	ft_putstr_fd(RED, STDERR_FILENO);
	ft_putendl_fd("Error", STDERR_FILENO);
	ft_putendl_fd(error_msg, STDERR_FILENO);
	ft_putstr_fd(RESET_COLOR, STDERR_FILENO);
	return (error_code);
}
