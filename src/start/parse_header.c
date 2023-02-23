/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_header.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 12:58:06 by ncotte            #+#    #+#             */
/*   Updated: 2023/02/23 12:58:08 by ncotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static int	*init_static(t_scene *scene, char **header_names, \
	int (*fct_header[])(void *, char *), void **item_ptr)
{
	int	*lengths;
	int	i;

	lengths = ft_calloc(NB_HEADER_INFO, sizeof(*lengths));
	if (!lengths)
		return (NULL);
	header_names[0] = "width";
	fct_header[0] = &parse_integer;
	item_ptr[0] = &scene->width;
	header_names[1] = "height";
	fct_header[1] = &parse_integer;
	item_ptr[1] = &scene->height;
	header_names[2] = "reflexions";
	fct_header[2] = &parse_integer;
	item_ptr[2] = &scene->reflexions;
	i = -1;
	while (++i < NB_HEADER_INFO)
		lengths[i] = (int)ft_strlen(header_names[i]);
	return (lengths);
}

static int	header_item(t_scene *scene, char *item, int index, int *flags)
{
	static int	(*fct_header[NB_HEADER_INFO])(void *, char *);
	static char	*header_names[NB_HEADER_INFO];
	static void	*item_ptr[NB_BONUS];
	static int	*lengths;

	if (!(*fct_header))
	{
		lengths = init_static(scene, header_names, fct_header, item_ptr);
		if (!lengths)
			return (print_error(ERROR_NEG, \
				"Internal allocation failed"));
	}
	if (ft_strncmp(item, header_names[index], lengths[index]))
		return (NO);
	if (item[lengths[index]] != '=')
		return (print_error(ERROR_NEG, \
			"Parameter format invalid: name=value"));
	if (*flags >> index & 0x00000001)
		return (print_error(ERROR_NEG, "Parameter already defined"));
	*flags |= 0x00000001 << index;
	if (fct_header[index](item_ptr[index], item + lengths[index] + 1))
		return (ERROR_NEG);
	return (YES);
}

int	parse_header(t_scene *scene, t_list *current, t_object *object)
{
	int		i;
	int		flags;
	int		value;
	int		total;
	char	*item;

	(void) object;
	if (scene->width)
		return (print_error(ERROR, \
			"There can be only one header per file"));
	flags = 0x00000000;
	item = next_item((char *)(current->content));
	while (item)
	{
		i = -1;
		total = 0;
		while (++i < NB_HEADER_INFO)
		{
			value = header_item(scene, item, i, &flags);
			if (value < 0)
				return (ERROR);
			total += value;
		}
		if (!total)
			return (print_error(ERROR, "Unknown parameter"));
		item = next_item(item);
	}
	if (!(flags & 0x00000001) ^ !(flags & 0x00000002))
		return (print_error(ERROR, \
			"The width and height must be both defined or none"));
	if ((!scene->width && flags & 0x00000001) \
		|| (!scene->height && flags & 0x00000002))
		return (print_error(ERROR, \
			"The width and height can not be equal to 0"));
	return (SUCCESS);
}
