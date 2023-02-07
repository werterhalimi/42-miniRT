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

	vector_p = sub_vectors(point, cylinder.coord);
	proj_p = scalar_multi(dot_product(vector_p, cylinder.direction) * \
		inv_sqrt(norm_square(cylinder.direction)), cylinder.direction);
	height_p = norm_square(proj_p);
	radius_p = norm_square(sub_vectors(vector_p, proj_p));
	if ((height_p == cylinder.semi_height * cylinder.semi_height \
		&& radius_p < cylinder.radius * cylinder.radius) \
		|| (height_p < cylinder.semi_height * cylinder.semi_height \
		&& radius_p == cylinder.radius * cylinder.radius))
		return (YES);
	return (NO);
}

static void	update_cylinder(t_scene *scene, void *object)
{
	t_cylinder	*cylinder;
	t_point		center_top;
	t_point		center_down;

	cylinder = (t_cylinder *)object;
	center_top = add_vectors(cylinder->coord, \
		scalar_multi(cylinder->semi_height, cylinder->direction));
	center_down = add_vectors(cylinder->coord, \
		scalar_multi(-cylinder->semi_height, cylinder->direction));
	cylinder->relative_center_top = sub_vectors(scene->camera->coord, center_top);
	cylinder->relative_center_down = sub_vectors(scene->camera->coord, center_down);
	cylinder->relative_coord = sub_vectors(scene->camera->coord, cylinder->coord);
	cylinder->value = dot_product(cylinder->relative_coord, cylinder->direction);
	cylinder->vector_quad = sub_vectors(cylinder->relative_coord, \
		scalar_multi(dot_product(cylinder->relative_coord, \
		cylinder->direction), cylinder->direction));
	cylinder->radius_square = cylinder->radius * cylinder->radius;
	cylinder->value_quad = norm_square(cylinder->vector_quad) \
		- cylinder->radius_square;
}

static double	cylinder_end(t_cylinder *cylinder, t_point ray, double div)
{
	double	t1;
	double	t2;

	t1 = (cylinder->semi_height + cylinder->value) / div;
	t2 = (-cylinder->semi_height + cylinder->value) / div;
	if (norm_square(add_vectors(scalar_multi(t1, ray), \
		cylinder->relative_center_top)) > cylinder->radius_square)
		t1 = INFINITY;
	if (norm_square(add_vectors(scalar_multi(t2, ray), \
		cylinder->relative_center_down)) > cylinder->radius_square)
		t2 = INFINITY;
	if (isfinite(t1) && t1 >= 0.0 && t1 < t2)
		return (t1);
	if (isfinite(t2) && t2 >= 0.0)
		return (t2);
	return (INFINITY);
}

static double	cylinder_side(t_cylinder *cylinder, t_point ray)
{
	double	t1;
	double	t2;
	double	limit;
	t_point	vector;

	vector = sub_vectors(ray, scalar_multi(dot_product(ray, \
		cylinder->direction), cylinder->direction));
	t1 = quad_solv(norm_square(vector), 2.0 * dot_product(vector, \
		cylinder->vector_quad), cylinder->value_quad, &t2);
	limit = dot_product(add_vectors(scalar_multi(t1, ray), \
		cylinder->relative_coord), cylinder->relative_coord);
	if (!isnan(t1) && t1 < t2 && t1 >= 0.0 \
		&& -cylinder->semi_height < limit && limit < cylinder->semi_height)
		return (t1);
	limit = dot_product(add_vectors(scalar_multi(t2, ray), \
		cylinder->relative_coord), cylinder->relative_coord);
	if (!isnan(t2) && t2 >= 0.0 \
		&& -cylinder->semi_height < limit && limit < cylinder->semi_height)
		return (t2);
	return (INFINITY);
}

static double	intersect_cylinder(t_point ray, void *object)
{
	t_cylinder	*cylinder;
	double		div;
	double		t1;
	double		t2;

	cylinder = (t_cylinder *)object;
	t1 = INFINITY;
	t2 = INFINITY;
	div = dot_product(ray, cylinder->direction);
	if (div)
		t1 = cylinder_end(cylinder, ray, div);
	if (-1.0 < div && div < 1.0)
		t2 = cylinder_side(cylinder, ray);
	if (isfinite(t1) && t1 >= 0.0 && t1 < t2)
		return (t1);
	if (isfinite(t2) && t2 >= 0.0)
		return (t2);
	return (INFINITY);
}

static unsigned int	get_color_cylinder(t_scene *scene, void *object)
{
	t_cylinder	*cylinder;

	(void)scene;
	cylinder = (t_cylinder *)object;
	return (color_trgb(cylinder->color));
}

static int	sub_parse_cylinder(t_cylinder *cylinder, t_list *current)
{
	char	*item;

	item = next_item((char *)(current->content));
	if (parse_coord(&(cylinder->coord), item))
		return (ERROR);
	item = next_item(item);
	if (parse_vector(&(cylinder->direction), item, YES))
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

int	parse_cylinder(t_scene *scene, t_list *current, t_objects *object)
{
	t_cylinder	*cylinder;

	(void)scene;
	object->type = CYLINDER;
	cylinder = ft_calloc(1, sizeof (t_cylinder));
	if (!cylinder)
		return (print_error(ERROR, "Cylinder allocation failed"));
	if (sub_parse_cylinder(cylinder, current))
		return (ERROR);
	object->object = cylinder;
	object->get_color = &get_color_cylinder;
	object->intersect = &intersect_cylinder;
	object->update = &update_cylinder;
	return (SUCCESS);
}
