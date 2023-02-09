/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_to_double.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 12:02:36 by ncotte            #+#    #+#             */
/*   Updated: 2023/01/30 12:02:40 by ncotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	str_to_double(char *str, double *d, int last)
{
	double	decimal;
	int		sign;
	int		i;

	*d = 0.0;
	sign = 1;
	i = 0;
	if (str[i] == '-' && ++i)
		sign = -1;
	while (ft_isdigit(str[i]))
		*d = *d * 10.0 + (double)(str[i++] - '0');
	if (str[i] == '.')
		i++;
	decimal = 10.0;
	while (ft_isdigit(str[i]))
	{
		*d = *d + (double)(str[i++] - '0') / decimal;
		decimal *= 10.0;
	}
	if (!last && (str[i] != ',' || !ft_isdigit(str[i - 1])))
		return (ERROR);
	if (last && str[i] && str[i] != '\n' && str[i] != ' ')
		return (ERROR);
	*d *= (double)sign;
	return (SUCCESS);
}
