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

static void	init_static(char **obj_names, \
	int (*fct_array[])(t_scene *, t_list *))
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

static int	parse_selector(t_scene *scene, t_list *current)
{
	static int	(*fct_array[NB_OBJECTS])(t_scene *, t_list *);
	static char	*obj_names[NB_OBJECTS];
	int			i;

	if (!(*fct_array))
		init_static(obj_names, fct_array);
	i = -1;
	while (++i < NB_OBJECTS)
		if (!ft_strncmp(current->content, obj_names[i], \
			ft_strlen(obj_names[i])))
			return (fct_array[i](scene, current));
	return (print_error(ERROR, "Unknown object"));
}

static int	objects_parsing(t_scene *scene, t_list **objects)
{
	scene->objects = ft_calloc(scene->nb_objects - 1, \
		sizeof (*(scene->objects)));
	if (!(scene->objects))
		return (print_error(ERROR, "Scene allocation failed"));
	scene->objects_type = ft_calloc(scene->nb_objects - 2, \
		sizeof (*(scene->objects_type)));
	if (!(scene->objects))
		return (print_error(ERROR, "Scene allocation failed"));
	while (*objects)
	{
		if (parse_selector(scene, *objects))
			return (ERROR);
		*objects = (*objects)->next;
	}
	ft_lstclear(objects, ft_free);
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
	return (print_window(scene));
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
	return (init_mlx(*scene));
}
