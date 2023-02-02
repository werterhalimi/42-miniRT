/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 19:28:07 by ncotte            #+#    #+#             */
/*   Updated: 2023/01/29 19:28:08 by ncotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	is_cylinder(t_point point, t_cylinder cylinder)
{
	t_point	vector_p;
	t_point	proj_p;
	double	height_p;
	double	radius_p;

	vector_p = vector_op(cylinder.coord, point);
	proj_p = scalar_multi(dot_product(vector_p, cylinder.vector) * \
		inv_sqrt(norm_square(cylinder.vector)), cylinder.vector);
	height_p = norm_square(proj_p);
	radius_p = norm_square(vector_op(proj_p, vector_p));
	if ((height_p == cylinder.semi_height * cylinder.semi_height \
		&& radius_p < cylinder.radius * cylinder.radius) \
		|| (height_p < cylinder.semi_height * cylinder.semi_height \
		&& radius_p == cylinder.radius * cylinder.radius))
		return (YES);
	return (NO);
}

static int	sub_parse_cylinder(t_cylinder *cylinder, t_list *current)
{
	char	*item;

	item = next_item((char *)(current->content));
	if (parse_coord(&(cylinder->coord), item))
		return (ERROR);
	item = next_item(item);
	if (parse_vector(&(cylinder->vector), item))
		return (ERROR);
	item = next_item(item);
	if (parse_length(&(cylinder->radius), item, "Diameter", YES))
		return (ERROR);
	item = next_item(item);
	if (parse_length(&(cylinder->semi_height), item, "Height", YES))
		return (ERROR);
	item = next_item(item);
	if (parse_color(&(cylinder->color), item))
		return (ERROR);
	if (next_item(item))
		return (print_error(ERROR, "Too many items for cylinder"));
	return (SUCCESS);
}

int	parse_cylinder(t_scene *scene, t_list *current)
{
	int			i;
	t_cylinder	*cylinder;

	i = 0;
	while ((scene->objects)[i])
		i++;
	cylinder = ft_calloc(1, sizeof (t_cylinder));
	if (!cylinder)
		return (print_error(ERROR, "Cylinder allocation failed"));
	if (sub_parse_cylinder(cylinder, current))
		return (ERROR);
	cylinder->type = CYLINDER;
	(scene->objects)[i] = cylinder;
	return (SUCCESS);
}
