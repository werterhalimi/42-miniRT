/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_length.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 13:42:46 by ncotte            #+#    #+#             */
/*   Updated: 2023/01/30 13:42:48 by ncotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static int	custom_error(char *prefix, char *name, char *suffix)
{
	ft_putstr_fd(RED, STDERR_FILENO);
	ft_putendl_fd("Error", STDERR_FILENO);
	ft_putstr_fd(prefix, STDERR_FILENO);
	ft_putstr_fd(name, STDERR_FILENO);
	ft_putendl_fd(suffix, STDERR_FILENO);
	ft_putstr_fd(RESET_COLOR, STDERR_FILENO);
	return (ERROR);
}

int	parse_length(double *length, char *item, char *name)
{
	if (!item)
		return (custom_error("A ", name, " is missing"));
	if (str_to_d(item, length, YES))
		return (custom_error("Invalid ", name, \
			" format. Required: one double"));
	if (*length < 0.0)
		return (custom_error("The ", name, " must be positive"));
	return (SUCCESS);
}
