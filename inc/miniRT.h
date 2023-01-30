/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 11:02:34 by ncotte            #+#    #+#             */
/*   Updated: 2023/01/29 11:02:36 by ncotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "../libft/libft.h"
# include "../mlx/mlx.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <errno.h>
# include <fcntl.h>
# include <math.h>

/* Color codes */

# define RESET_COLOR		"\033[0m"
# define BLACK				"\033[0m\033[30m"
# define RED				"\033[0m\033[31m"
# define GREEN				"\033[0m\033[32m"
# define YELLOW				"\033[0m\033[33m"
# define BLUE				"\033[0m\033[34m"
# define MAGENTA			"\033[0m\033[35m"
# define CYAN				"\033[0m\033[36m"
# define WHITE				"\033[0m\033[37m"
# define BOLD_BLACK			"\033[1m\033[30m"
# define BOLD_RED			"\033[1m\033[31m"
# define BOLD_GREEN			"\033[1m\033[32m"
# define BOLD_YELLOW		"\033[1m\033[33m"
# define BOLD_BLUE			"\033[1m\033[34m"
# define BOLD_MAGENTA		"\033[1m\033[35m"
# define BOLD_CYAN			"\033[1m\033[36m"
# define BOLD_WHITE			"\033[1m\033[37m"

/* Error/return codes */

# define SUCCESS	0
# define ERROR		1
# define ERROR_NEG	-1

/* Bool codes */

# define NO			0
# define YES		1

/* Number of objects */

# define NB_OBJECTS	6

/* Structures */

typedef struct s_point
{
	double	x;
	double	y;
	double	z;
}	t_point;

typedef struct s_color
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
}	t_color;

typedef struct s_amb_light
{
	t_color	color;
	double	ratio;
}	t_amb_light;

typedef struct s_camera
{
	t_point	coord;
	t_point	vector;
	double	fov;
}	t_camera;

typedef struct s_light
{
	t_point	coord;
	t_color	color;
	double	ratio;
}	t_light;

typedef struct s_sphere
{
	t_point	coord;
	t_color	color;
	double	diameter;
}	t_sphere;

typedef struct s_plane
{
	t_point	coord;
	t_point	vector;
	t_color	color;
}	t_plane;

typedef struct s_cylinder
{
	t_point	coord;
	t_point	vector;
	t_color	color;
	double	diameter;
	double	height;
}	t_cylinder;

typedef struct s_scene
{
	t_amb_light	*amb_light;
	t_camera	*camera;
	t_light		*light;
	void		**objects;
}	t_scene;

/* utils */

int		print_error(int error_code, char *error_msg);

int		str_to_d(char *str, double *d, int last);

/* items */

int		parse_color(t_color *color, char *item);

int		parse_ratio(double *ratio, char *item);

int		parse_length(double *length, char *item, char *name);

char	*next_coord(char *item, char last);

int		parse_coord(t_point *coord, char *item);

int		parse_vector(t_point *vector, char *item);

/* objects */

int		parse_amb_light(t_scene *scene, t_list *current);

int		parse_camera(t_scene *scene, t_list *current);

int		parse_light(t_scene *scene, t_list *current);

int		parse_sphere(t_scene *scene, t_list *current);

int		parse_plane(t_scene *scene, t_list *current);

int		parse_cylinder(t_scene *scene, t_list *current);

/* init */

char	*next_item(char *line);

int		read_file(int argc, char **argv, t_list **objects);

int		init(int argc, char **argv, t_scene **scene);

#endif
