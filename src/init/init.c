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

static t_scene	*alloc_scene(int size)
{
	t_scene	*scene;

	scene = ft_alloc(1, sizeof (*scene), NULL, ALLOC);
	if (!scene || size < 4)
		return (scene);
	scene->objects = ft_alloc(size - 2, sizeof (*(scene->objects)), \
		NULL, ALLOC);
	if (!(scene->objects))
		return (NULL);
	return (scene);
}

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

static int	parse_selector(t_scene **scene, t_list *current)
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
			return (fct_array[i](*scene, current));
	return (print_error(ERROR, "Unknown object"));
}

static int	check_scene(t_scene *scene, t_list **objects)
{
	(void) objects;
	ft_lstclear(objects, ft_free);
	if (!(scene->amb_light))
		return (print_error(ERROR, "An ambient light is missing"));
	if (!(scene->camera))
		return (print_error(ERROR, "A camera is missing"));
	if (!(scene->light))
		return (print_error(ERROR, "A main light is missing"));
	return (SUCCESS);
}

int	init(int argc, char **argv, t_scene **scene)
{
	t_list	*objects;
	t_list	*current;
	int		size;

	objects = NULL;
	size = read_file(argc, argv, &objects);
	if (size < 0)
		return (ERROR);
	*scene = alloc_scene(size);
	if (!(*scene))
		return (print_error(ERROR, "Scene allocation failed"));
	current = objects;
	while (current)
	{
		if (parse_selector(scene, current))
			return (ERROR);
		current = current->next;
	}
	return (check_scene(*scene, &objects));
}
