/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 14:43:27 by ncotte            #+#    #+#             */
/*   Updated: 2023/02/16 23:21:39 by shalimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	init_arrays(char **obj_names, \
	int (*fct_array[])(t_scene *, t_list *, t_object *))
{
	obj_names[0] = "H ";
	fct_array[0] = &parse_header;
	obj_names[1] = "A ";
	fct_array[1] = &parse_amb_light;
	obj_names[2] = "C ";
	fct_array[2] = &parse_camera;
	obj_names[3] = "L ";
	fct_array[3] = &parse_light;
	obj_names[4] = "sp ";
	fct_array[4] = &parse_sphere;
	obj_names[5] = "pl ";
	fct_array[5] = &parse_plane;
	obj_names[6] = "cy ";
	fct_array[6] = &parse_cylinder;
	obj_names[7] = "co ";
	fct_array[7] = &parse_cone;
	obj_names[8] = "sl ";
	fct_array[8] = &parse_spot_light;
}

static int	parse_selector(t_scene *scene, t_list *current, char *obj_names[], \
	int (*fct_array[])(t_scene *, t_list *, t_object *))
{
	int	i;
	int	j;

	i = -1;
	while (++i < NB_ITEMS)
	{
		if (!ft_strncmp(current->content, obj_names[i], \
			ft_strlen(obj_names[i])))
		{
			if (i < NB_NON_OBJECTS_ITEMS)
				return (fct_array[i](scene, current, NULL));
			j = 0;
			if (i > NB_NON_OBJECTS_ITEMS)
				j = 1;
			while (scene->objects[j])
				j++;
			scene->objects[j] = ft_calloc(1, sizeof (t_object));
			if (!scene->objects[j])
				return (print_error(ERROR, "Object allocation failed"));
			return (fct_array[i](scene, current, scene->objects[j]));
		}
	}
	return (print_error(ERROR, "Unknown object"));
}

static int	objects_parsing(t_scene *scene, t_list **list)
{
	int		(*fct_array[NB_ITEMS])(t_scene *, t_list *, t_object *);
	char	*obj_names[NB_ITEMS];

	scene->objects = ft_calloc(scene->nb_objects + 1, \
		sizeof (*scene->objects));
	if (!(scene->objects))
		return (print_error(ERROR, "Objects allocation failed"));
	init_arrays(obj_names, fct_array);
	while (*list)
	{
		if (parse_selector(scene, *list, obj_names, fct_array))
			return (ERROR);
		*list = (*list)->next;
	}
	ft_lstclear(list, ft_free);
	if (!scene->amb_light)
		return (print_error(ERROR, "An ambient light is missing"));
	if (!scene->camera)
		return (print_error(ERROR, "A camera is missing"));
	if (!scene->light)
		return (print_error(ERROR, "A main light is missing"));
	return (SUCCESS);
}

static int	init_mlx(t_scene *scene)
{
	scene->mlx = mlx_init();
	if (!scene->mlx)
		return (print_error(ERROR, "MLX initialization has failed"));
	scene->window = mlx_new_window(scene->mlx, \
		scene->width, scene->height, "miniRT");
	if (!scene->window)
		return (print_error(ERROR, "Windows initialization has failed"));
	scene->image = mlx_new_image(scene->mlx, \
		scene->width, scene->height);
	if (!scene->image)
		return (print_error(ERROR, "Image initialization has failed"));
	scene->address = mlx_get_data_addr(scene->image, &scene->bpp, \
		&scene->line_len, &scene->endian);
	if (!scene->address)
		return (print_error(ERROR, "Image address not found"));
	print_window(scene, 1, scene->reflexions);
	return (SUCCESS);
}

int	init(int argc, char **argv, t_scene **scene)
{
	t_list	*objects;

	objects = NULL;
	*scene = ft_calloc(1, sizeof (**scene));
	if (!(*scene))
		return (print_error(ERROR, "Scene allocation failed"));
	(*scene)->nb_objects = read_file(argc, argv, &objects);
	if ((*scene)->nb_objects < 0)
		return (ERROR);
	if (objects_parsing(*scene, &objects))
		return (ERROR);
	if (!(*scene)->width)
	{
		(*scene)->width = 1920;
		(*scene)->height = 1080;
	}
	update_scene(*scene, UPDATE_ALL);
	return (init_mlx(*scene));
}
