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
//# include <string.h>
# include <limits.h>
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

/* Objects */
enum {
	MAIN_LIGHT = 0,
	SPHERE = 1,
	PLANE = 2,
	CYLINDER = 3
};

/// @brief Hooks
enum {
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_MOUSEDOWN = 4,
	ON_MOUSEUP = 5,
	ON_MOUSEMOVE = 6,
	ON_EXPOSE = 12,
	ON_DESTROY = 17
};

/// @brief Mouse buttons
enum {
	LEFT_CLICK = 1,
	RIGHT_CLICK = 2,
	MIDDLE_CLICK = 3,
	SCROLL_UP = 4,
	SCROLL_DOWN = 5
};

/// @brief Keyboard buttons
enum {
	KEY_ESC = 53,
	KEY_SPACE = 49,
	KEY_LEFT = 123,
	KEY_RIGHT = 124,
	KEY_DOWN = 125,
	KEY_UP = 126,
	KEY_PLUS = 69,
	KEY_MINUS = 78,
	KEY_LEFT_SHIFT = 57,
	KEY_K = 40,
	KEY_R = 15,
	KEY_G = 5,
	KEY_B = 11,
	KEY_Y = 16,
	KEY_C = 8,
	KEY_M = 46,
	KEY_D = 2,
	KEY_W = 13,
	KEY_S = 1,
	KEY_PAGE_UP = 116,
	KEY_PAGE_DOWN = 121
};

/* Structures */

struct s_scene;

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
	t_point	front;
	t_point	right;
	t_point	down;
	t_point	shift_x;
	t_point	shift_y;
	double	fov;
	double	pixel_size;
	double	size_x;
	double	size_y;
}	t_camera;

typedef struct s_light
{
	t_point	coord;
	t_point	relative_coord;
	t_color	color;
	double	ratio;
}	t_light;

typedef struct s_sphere
{
	t_point	coord;
	t_point	relative_coord;
	t_color	color;
	double	radius;
	double	value;
}	t_sphere;

typedef struct s_plane
{
	t_point	coord;
	t_point	normal;
	t_color	color;
	double	value;
}	t_plane;

typedef struct s_cylinder
{
	t_point	coord;
	t_point	relative_coord;
	t_point	direction;
	t_point	center_top;
	t_point	center_down;
	t_point	relative_center_top;
	t_point	relative_center_down;
	t_point	vector_quad;
	t_color	color;
	double	radius;
	double	radius_square;
	double	semi_height;
	double	value;
	double	value_quad;
}	t_cylinder;

typedef struct s_objects
{
	void			*object;
	unsigned int	(*get_color)(struct s_scene *, void *);
	double 			(*intersect)(t_point, void *);
	void			(*update)(struct s_scene *, void *);
	int 			type;
}	t_objects;

typedef struct s_scene
{
	t_point		window_corner;
	t_amb_light	*amb_light;
	t_camera	*camera;
	t_light		*light;
	t_objects	**objects;
	void		*mlx;
	void		*window;
	void		*image;
	char		*address;
	int			bpp;
	int			line_len;
	int			endian;
	int			width;
	int			height;
}	t_scene;

/* utils */

void			quit(t_scene *scene);

int				key_hook(int key_code, t_scene *scene);

int				mouse_hook(int mouse_code, int x, int y, t_scene *scene);

int				print_error(int error_code, char *error_msg);

int				str_to_d(char *str, double *d, int last);

double			inv_sqrt(double d);

double			quad_solv(double a, double b, double c, double *x);

/* items */

int				parse_color(t_color *color, char *item);

int				parse_ratio(double *ratio, char *item);

int				parse_length(double *length, char *item, char *name, char half);
/*
double			dist_op(t_point o, t_point p);
*/
char			*next_coord(char *item, char last);

int				parse_coord(t_point *coord, char *item);

int				is_null(t_point vector);

t_point			add_vectors(t_point v1, t_point v2);

t_point			sub_vectors(t_point v1, t_point v2);
/*
double			norm_vector(t_point normal);
*/
t_point			scalar_multi(double lambda, t_point vector);

t_point			cross_product(t_point v1, t_point v2);

double			dot_product(t_point v1, t_point v2);

double			norm_square(t_point vector);

t_point			unit_vector(t_point vector);

int				parse_vector(t_point *vector, char *item, char norm);

/* objects */

int				parse_amb_light(t_scene *scene, t_list *current, t_objects *object);

int				parse_camera(t_scene *scene, t_list *current, t_objects *object);

int				parse_light(t_scene *scene, t_list *current, t_objects *object);

int				is_sphere(t_point point, t_sphere sphere);

int				parse_sphere(t_scene *scene, t_list *current, t_objects *object);

int				is_plane(t_point point, t_plane plane);

int				parse_plane(t_scene *scene, t_list *current, t_objects *object);

int				is_cylinder(t_point point, t_cylinder cylinder);

int				parse_cylinder(t_scene *scene, t_list *current, t_objects *object);

/* print */

unsigned int	create_trgb(unsigned char t, unsigned char r, \
					unsigned char g, unsigned char b);

unsigned int	color_trgb(t_color color);

unsigned char	color_get_t(int trgb);

unsigned char	color_get_r(int trgb);

unsigned char	color_get_g(int trgb);

unsigned char	color_get_b(int trgb);

void			put_pixel(t_scene *scene, int x, int y, unsigned int color);

int 			print_window(t_scene *scene);

/* init */

char			*next_item(char *line);

int				read_file(int argc, char **argv, t_list **objects);

int				init(int argc, char **argv, t_scene **scene);

#endif
