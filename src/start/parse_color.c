/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 10:41:53 by ncotte            #+#    #+#             */
/*   Updated: 2023/02/17 21:46:45 by shalimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static char	*next_color(char *item, char last)
{
	while (ft_isdigit(*item))
		item++;
	if (last && (!(*item) || *item == '\n' || *item == ' '))
		return (NULL);
	else if (last)
		return (item);
	if (*item != ',')
		return (NULL);
	if (ft_isdigit(*(++item)))
		return (item);
	return (NULL);
}

static int	set_color(unsigned char *color, char const *item)
{
	int	c;
	int	i;

	if (!item)
		return (print_error(ERROR, \
			"Invalid color format. Expected: R,G,B"));
	c = 0;
	i = 0;
	while (ft_isdigit(item[i]) && i < 3)
		c = c * 10 + (item[i++] - '0');
	if ((item[i] && item[i] != '\n' && item[i] != ' ' && item[i] != ',') \
		|| c > 255)
		return (print_error(ERROR, \
			"The color components must be included in {0; ...; 255}"));
	*color = (unsigned char) c;
	return (SUCCESS);
}

int	parse_color(t_color *color, char *item)
{
	if (!item)
		return (print_error(ERROR, "A color is missing"));
	if (set_color(&color->r, item))
		return (ERROR);
	item = next_color(item, NO);
	if (set_color(&color->g, item))
		return (ERROR);
	item = next_color(item, NO);
	if (set_color(&color->b, item))
		return (ERROR);
	if (next_color(item, YES))
		return (print_error(ERROR, "Too many color components"));
	return (SUCCESS);
}

int	parse_color_bonus(t_object *object, char *item)
{
	object->color_bis = ft_calloc(1, sizeof (*object->color_bis));
	if (!object->color_bis || parse_color(object->color_bis, item))
		return (ERROR);
	return (SUCCESS);
}
