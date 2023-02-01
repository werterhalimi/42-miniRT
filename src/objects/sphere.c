/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 19:27:39 by ncotte            #+#    #+#             */
/*   Updated: 2023/01/29 19:27:40 by ncotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	parse_sphere(t_scene *scene, t_list *current)
{
	int			i;
	char		*item;
	t_sphere	*sphere;

	i = 0;
	while ((scene->objects)[i])
		i++;
	sphere = ft_calloc(1, sizeof (t_sphere));
	if (!sphere)
		return (print_error(ERROR, "Sphere allocation failed"));
	item = next_item((char *)(current->content));
	if (parse_coord(&(sphere->coord), item))
		return (ERROR);
	item = next_item(item);
	if (parse_length(&(sphere->diameter), item, "Diameter"))
		return (ERROR);
	item = next_item(item);
	if (parse_color(&(sphere->color), item))
		return (ERROR);
	if (next_item(item))
		return (print_error(ERROR, "Too many items for sphere"));
	(scene->objects)[i] = sphere;
	return (SUCCESS);
}
