/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 13:50:00 by ncotte            #+#    #+#             */
/*   Updated: 2023/02/22 17:36:34 by shalimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	init_static(char **bonus_names, \
	int (*fct_bonus[])(t_object *, char *), int lengths[])
{
	int	i;

	bonus_names[0] = "checkerboard";
	fct_bonus[0] = &parse_color_bonus;
	bonus_names[1] = "specular";
	fct_bonus[1] = &parse_specular;
	bonus_names[2] = "texture";
	fct_bonus[2] = &parse_texture;
	bonus_names[3] = "normal_map";
	fct_bonus[3] = &parse_normal_map;
	i = -1;
	while (++i < NB_BONUS)
		lengths[i] = (int)ft_strlen(bonus_names[i]);
}

static int	item_bonus(t_object *object, char *item, int index, int *flags)
{
	static int	(*fct_bonus[NB_BONUS])(t_object *, char *);
	static char	*bonus_names[NB_BONUS];
	static int	lengths[NB_BONUS];

	if (!(*fct_bonus))
		init_static(bonus_names, fct_bonus, lengths);
	if (ft_strncmp(item, bonus_names[index], lengths[index]))
		return (NO);
	if (item[lengths[index]] != '=')
		return (print_error(ERROR_NEG, \
			"Parameter format invalid: name=value"));
	if (*flags >> index & 0x00000001)
		return (print_error(ERROR_NEG, "Parameter already defined"));
	*flags |= 0x00000001 << index;
	if (fct_bonus[index](object, item + lengths[index] + 1))
		return (ERROR_NEG);
	return (YES);
}

int	parse_bonus(t_object *object, char *item)
{
	int	flags;
	int	value;
	int	total;
	int	i;

	flags = 0x00000000;
	while (item)
	{
		i = -1;
		total = 0;
		while (++i < NB_BONUS)
		{
			value = item_bonus(object, item, i, &flags);
			if (value < 0)
				return (ERROR);
			total += value;
		}
		if (!total)
			return (print_error(ERROR, "Unknown parameter"));
		item = next_item(item);
	}
	return (SUCCESS);
}
