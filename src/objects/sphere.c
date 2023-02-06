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

int	is_sphere(t_point point, t_sphere sphere)
{
	if (norm_square(sub_vectors(point, sphere.coord)) \
		== sphere.radius * sphere.radius)
		return (YES);
	return (NO);
}

static void	update_sphere(t_scene *scene, void *object)
{
	t_sphere	*sphere;

	sphere = (t_sphere *)object;
	sphere->relative_coord = sub_vectors(scene->camera->coord, sphere->coord);
	sphere->value = norm_square(sphere->relative_coord) \
		- sphere->radius * sphere->radius;
}

static double	intersect_sphere(t_point ray, void *object)
{
	t_sphere	*sphere;
	double		t1;
	double		t2;

	sphere = (t_sphere *)object;
	t1 = quad_solv(1, 2.0 * dot_product(ray, \
		sphere->relative_coord), sphere->value, &t2);
	if (!isnan(t1) && t1 < t2 && t1 >= 0.0)
		return (t1);
	if (!isnan(t2) && t2 >= 0.0)
		return (t2);
	return (INFINITY);
}

static unsigned int	get_color_sphere(t_scene *scene, void *object)
{
	t_sphere	*sphere;

	(void)scene;
	sphere = (t_sphere *)object;
	return (color_trgb(sphere->color));
}

int	parse_sphere(t_scene *scene, t_list *current, t_objects *object)
{
	char		*item;
	t_sphere	*sphere;

	(void)scene;
	object->type = SPHERE;
	sphere = ft_calloc(1, sizeof (t_sphere));
	if (!sphere)
		return (print_error(ERROR, "Sphere allocation failed"));
	item = next_item((char *)(current->content));
	if (parse_coord(&(sphere->coord), item))
		return (ERROR);
	item = next_item(item);
	if (parse_length(&(sphere->radius), item, "Diameter", YES))
		return (ERROR);
	item = next_item(item);
	if (parse_color(&(sphere->color), item))
		return (ERROR);
	if (next_item(item))
		return (print_error(ERROR, "Too many items for sphere"));
	object->object = sphere;
	object->get_color = &get_color_sphere;
	object->intersect = &intersect_sphere;
	object->update = &update_sphere;
	return (SUCCESS);
}
