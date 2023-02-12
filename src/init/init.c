/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 14:43:27 by ncotte            #+#    #+#             */
/*   Updated: 2023/01/29 14:43:33 by ncotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	init_arrays(char **obj_names, \
	int (*fct_array[])(t_scene *, t_list *, t_objects *))
{
	obj_names[0] = "A ";
	fct_array[0] = &parse_amb_light;
	obj_names[1] = "C ";
	fct_array[1] = &parse_camera;
	obj_names[2] = "L ";
	fct_array[2] = &parse_light;
	obj_names[3] = "sp ";
	fct_array[3] = &parse_sphere;
	obj_names[4] = "pl ";
	fct_array[4] = &parse_plane;
	obj_names[5] = "cy ";
	fct_array[5] = &parse_cylinder;
}

static int	parse_selector(t_scene *scene, t_list *current, char *obj_names[], \
	int (*fct_array[])(t_scene *, t_list *, t_objects *))
{
	int			i;
	int			j;

	i = -1;
	while (++i < NB_OBJECTS)
	{
		if (!ft_strncmp(current->content, obj_names[i], \
			ft_strlen(obj_names[i])))
		{
			if (i < 2)
				return (fct_array[i](scene, current, NULL));
			j = 0;
			if (i > 2)
				j = 1;
			while ((scene->objects)[j])
				j++;
			(scene->objects)[j] = ft_calloc(1, sizeof (t_objects));
			if (!(scene->objects)[j])
				return (print_error(ERROR, "Object allocation failed"));
			return (fct_array[i](scene, current, (scene->objects)[j]));
		}
	}
	return (print_error(ERROR, "Unknown object"));
}

static int	objects_parsing(t_scene *scene, t_list **list)
{
	int		(*fct_array[NB_OBJECTS])(t_scene *, t_list *, t_objects *);
	char	*obj_names[NB_OBJECTS];

	scene->objects = ft_calloc(scene->nb_objects + 1, \
		sizeof (*(scene->objects)));
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
	if (!(scene->amb_light))
		return (print_error(ERROR, "An ambient light is missing"));
	if (!(scene->camera))
		return (print_error(ERROR, "A camera is missing"));
	if (!(scene->light))
		return (print_error(ERROR, "A main light is missing"));
	return (SUCCESS);
}

static int	init_mlx(t_scene *scene)
{
	scene->mlx = mlx_init();
	if (!(scene->mlx))
		return (print_error(ERROR, "MLX initialization has failed"));
	scene->window = mlx_new_window(scene->mlx, \
		scene->width, scene->height, "miniRT");
	if (!(scene->window))
		return (print_error(ERROR, "Windows initialization has failed"));
	scene->image = mlx_new_image(scene->mlx, \
		scene->width, scene->height);
	if (!(scene->image))
		return (print_error(ERROR, "Image initialization has failed"));
	scene->address = mlx_get_data_addr(scene->image, &scene->bpp, \
		&scene->line_len, &scene->endian);
	if (!(scene->address))
		return (print_error(ERROR, "Image address not found"));
	print_window(scene, 1);
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
	(*scene)->width = 1920;
	(*scene)->height = 1080;
	if (objects_parsing(*scene, &objects))
		return (ERROR);
	update_scene(*scene, UPDATE_ALL);
	return (init_mlx(*scene));
}
