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
	proj_p = scalar_multi(dot_product(vector_p, \
		cylinder.direction), cylinder.direction);
	height_p = norm_square(proj_p);
	radius_p = norm_square(sub_vectors(vector_p, proj_p));
	if ((height_p == cylinder.semi_height_square \
		&& radius_p < cylinder.radius_square) \
		|| (height_p < cylinder.semi_height_square \
		&& radius_p == cylinder.radius_square))
		return (YES);
	return (NO);
}

static void	update_top_down(t_cylinder *cy, t_point eye, unsigned int flags)
{
	static t_point	center_top;
	static t_point	center_down;

	if (flags & CYLINDER_ALL)
	{
		center_top = add_vectors(cy->coord, cy->vector_semi_height);
		center_down = add_vectors(cy->coord, \
			scalar_multi(-cy->semi_height, cy->direction));
	}
	cy->value_semi_height = dot_product(cy->relative_coord, \
		cy->vector_semi_height);
	cy->relative_center_top = sub_vectors(center_top, eye);
	cy->relative_center_down = sub_vectors(center_down, eye);
	cy->value_top = dot_product(cy->relative_center_top, cy->direction);
	cy->value_down = dot_product(cy->relative_center_down, cy->direction);
}

void	update_cylinder(t_scene *scene, void *object, unsigned int flags)
{
	t_cylinder	*cy;

	if (!(flags & (CAMERA_TRANSLATION | CYLINDER_ALL)))
		return ;
	cy = (t_cylinder *)object;
	if (flags & CYLINDER_RADIUS)
		cy->radius_square = cy->radius * cy->radius;
	if (flags & CYLINDER_HEIGHT)
		cy->semi_height_square = cy->semi_height * cy->semi_height;
	if (flags & (CYLINDER_HEIGHT | CYLINDER_ROTATION))
		cy->vector_semi_height = scalar_multi(cy->semi_height, cy->direction);
	if (flags & (CYLINDER_TRANSLATION | CAMERA_TRANSLATION))
		cy->relative_coord = sub_vectors(scene->camera->coord, cy->coord);
	if (flags & (CYLINDER_ROTATION | CYLINDER_TRANSLATION | CAMERA_TRANSLATION))
		cy->value = dot_product(cy->relative_coord, cy->direction);
	if (flags == UPDATE_ALL \
		|| flags & ((CYLINDER_ALL & ~CYLINDER_RADIUS) | CAMERA_TRANSLATION))
		update_top_down(cy, scene->camera->coord, flags);
	if (flags == UPDATE_ALL \
		|| flags & ((CYLINDER_ALL & ~CYLINDER_HEIGHT) | CAMERA_TRANSLATION))
		cy->value_quad = norm_square(cy->relative_coord) \
			- cy->value * cy->value - cy->radius_square;
}

static double	cylinder_end(t_cylinder *cylinder, t_point ray, double div)
{
	double	t1;
	double	t2;

	t1 = cylinder->value_top / div;
	t2 = cylinder->value_down / div;
	if (norm_square(sub_vectors(scalar_multi(t1, ray), \
		cylinder->relative_center_top)) > cylinder->radius_square)
		t1 = INFINITY;
	if (norm_square(sub_vectors(scalar_multi(t2, ray), \
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
	double	value;

	value = dot_product(ray, cylinder->direction);
	t1 = quad_solv(1 - value * value, 2.0 * (dot_product(ray, \
		cylinder->relative_coord) - value * cylinder->value), \
		cylinder->value_quad, &t2);
	if (!isnan(t1))
	{
		value = dot_product(ray, cylinder->vector_semi_height);
		limit = t1 * value + cylinder->value_semi_height;
		if (t1 >= 0.0 && -(cylinder->semi_height_square) < limit \
			&& limit < cylinder->semi_height_square && t1 < t2)
			return (t1);
		limit = t2 * value + cylinder->value_semi_height;
		if (t2 >= 0.0 && -(cylinder->semi_height_square) < limit \
			&& limit < cylinder->semi_height_square)
			return (t2);
	}
	return (INFINITY);
}

double	intersect_cylinder(t_point ray, void *object)
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
	if (-1.0 != div && div != 1.0)
		t2 = cylinder_side(cylinder, ray);
	if (isfinite(t1) && t1 >= 0.0 && t1 < t2)
		return (t1);
	if (isfinite(t2) && t2 >= 0.0)
		return (t2);
	return (INFINITY);
}

void	translation_relative_cylinder(int key_code, t_scene *scene)
{
	t_point		vector;
	t_cylinder	*cylinder;

	cylinder = (t_cylinder *)(scene->objects[scene->index - 1]->object);
	if (key_code == KEY_W)
		vector = scalar_multi(TRANSLATION_FACTOR, cylinder->direction);
	else if (key_code == KEY_S)
		vector = scalar_multi(-TRANSLATION_FACTOR, cylinder->direction);
	else
		return ;
	cylinder->coord = add_vectors(cylinder->coord, vector);
	update_scene(scene, PLANE_TRANSLATION);
}

void	rotation_relative_cylinder(int key_code, t_scene *scene)
{
	t_cylinder	*cylinder;

	cylinder = (t_cylinder *)(scene->objects[scene->index - 1]->object);
	if (key_code == NUMPAD_2)
		cylinder->down = matrix_vector_multi(matrix_rotation_relative(cylinder->right, \
			sin_rot()), cylinder->down);
	else if (key_code == NUMPAD_8)
		cylinder->down = matrix_vector_multi(matrix_rotation_relative(cylinder->right, \
			n_sin_rot()), cylinder->down);
	else if (key_code == NUMPAD_4)
		cylinder->right = matrix_vector_multi(matrix_rotation_relative(cylinder->down, \
			n_sin_rot()), cylinder->right);
	else if (key_code == NUMPAD_6)
		cylinder->right = matrix_vector_multi(matrix_rotation_relative(cylinder->down, \
			sin_rot()), cylinder->right);
	else
		return ;
	cylinder->direction = cross_product(cylinder->right, cylinder->down);
	update_scene(scene, CYLINDER_ROTATION);
}

void	translation_absolute_cylinder(t_scene *scene, t_point vector)
{
	t_cylinder	*cylinder;

	cylinder = (t_cylinder *)(scene->objects[scene->index - 1]->object);
	cylinder->coord = add_vectors(cylinder->coord, vector);
	update_scene(scene, CYLINDER_TRANSLATION);
}

void	rotation_absolute_cylinder(t_scene *scene, t_matrix matrix)
{
	t_cylinder	*cylinder;

	cylinder = (t_cylinder *)(scene->objects[scene->index - 1]->object);
	cylinder->direction = matrix_vector_multi(matrix, cylinder->direction);
	cylinder->right = matrix_vector_multi(matrix, cylinder->right);
	cylinder->down = cross_product(cylinder->direction, cylinder->right);
	update_scene(scene, CYLINDER_ROTATION);
}

unsigned int	get_color_cylinder(t_scene *scene, void *object)
{
	t_cylinder	*cylinder;

	(void)scene;
	cylinder = (t_cylinder *)object;
	return (color_trgb(cylinder->color));
}
