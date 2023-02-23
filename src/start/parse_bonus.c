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

static int	*init_static(char **bonus_names, int (*fct_bonus[])(void *, char *))
{
	int	*lengths;
	int	i;

	lengths = ft_calloc(NB_BONUS, sizeof(*lengths));
	if (!lengths)
		return (NULL);
	bonus_names[0] = "checkerboard";
	fct_bonus[0] = &parse_color_bonus;
	bonus_names[1] = "specular";
	fct_bonus[1] = &parse_integer;
	bonus_names[2] = "texture";
	fct_bonus[2] = &parse_texture;
	bonus_names[3] = "normal_map";
	fct_bonus[3] = &parse_normal_map;
	bonus_names[4] = "reflectance";
	fct_bonus[4] = &parse_ratio;
	i = -1;
	while (++i < NB_BONUS)
		lengths[i] = (int)ft_strlen(bonus_names[i]);
	return (lengths);
}

static void	get_address(t_object *object, void *item_ptr[])
{
	item_ptr[0] = &object->color_bis;
	item_ptr[1] = &object->specular;
	item_ptr[2] = &object->texture;
	item_ptr[3] = &object->normal_map;
	item_ptr[4] = &object->reflectance;
}

static int	item_bonus(t_object *object, char *item, int index, int *flags)
{
	static int	(*fct_bonus[NB_BONUS])(void *, char *);
	static char	*bonus_names[NB_BONUS];
	static int	*lengths;
	void		*item_ptr[NB_BONUS];

	if (!(*fct_bonus))
	{
		lengths = init_static(bonus_names, fct_bonus);
		if (!lengths)
			return (print_error(ERROR_NEG, \
				"Internal allocation failed"));
	}
	get_address(object, item_ptr);
	if (ft_strncmp(item, bonus_names[index], lengths[index]))
		return (NO);
	if (item[lengths[index]] != '=')
		return (print_error(ERROR_NEG, \
			"Parameter format invalid: name=value"));
	if (*flags >> index & 0x00000001)
		return (print_error(ERROR_NEG, "Parameter already defined"));
	*flags |= 0x00000001 << index;
	if (fct_bonus[index](item_ptr[index], item + lengths[index] + 1))
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
