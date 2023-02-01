/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   amb_light.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 19:27:30 by ncotte            #+#    #+#             */
/*   Updated: 2023/01/29 19:27:32 by ncotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	parse_amb_light(t_scene *scene, t_list *current)
{
	char		*item;
	t_amb_light	*amb_light;

	amb_light = scene->amb_light;
	if (amb_light)
		return (print_error(ERROR, \
			"There can be only one ambient light per scene"));
	amb_light = ft_calloc(1, sizeof (t_amb_light));
	printf("parse_amb_light : amb_light : %p\n", amb_light); // TODO
	if (!amb_light)
		return (print_error(ERROR, "Ambient light allocation failed"));
	item = next_item((char *)(current->content));
	if (parse_ratio(&(amb_light->ratio), item))
		return (ERROR);
	item = next_item(item);
	if (parse_color(&(amb_light->color), item))
		return (ERROR);
	if (next_item(item))
		return (print_error(ERROR, "Too many items for ambient light"));
	scene->amb_light = amb_light;
	return (SUCCESS);
}
