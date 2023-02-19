/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 11:02:34 by ncotte            #+#    #+#             */
/*   Updated: 2023/02/17 21:31:42 by shalimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "../libft/libft.h"
# include "../mlx/mlx.h"
# include "hooks.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
//# include <string.h>
# include <limits.h>
# include <errno.h>
# include <fcntl.h>
# include <float.h>
# include <math.h>

/* Color codes */

# define RESET_COLOR			"\033[0m"
# define BLACK					"\033[0m\033[30m"
# define RED					"\033[0m\033[31m"
# define GREEN					"\033[0m\033[32m"
# define YELLOW					"\033[0m\033[33m"
# define BLUE					"\033[0m\033[34m"
# define MAGENTA				"\033[0m\033[35m"
# define CYAN					"\033[0m\033[36m"
# define WHITE					"\033[0m\033[37m"
# define BOLD_BLACK				"\033[1m\033[30m"
# define BOLD_RED				"\033[1m\033[31m"
# define BOLD_GREEN				"\033[1m\033[32m"
# define BOLD_YELLOW			"\033[1m\033[33m"
# define BOLD_BLUE				"\033[1m\033[34m"
# define BOLD_MAGENTA			"\033[1m\033[35m"
# define BOLD_CYAN				"\033[1m\033[36m"
# define BOLD_WHITE				"\033[1m\033[37m"

/* Error/return codes */

# define SUCCESS				0
# define ERROR					1
# define ERROR_NEG				-1

/* Bool codes */

# define NO						0
# define YES					1

/* Move modes */

# define RELATIVE_MODE				0
# define ABSOLUTE_MODE				1

/* Updates flags */

# define CAMERA_TRANSLATION		0x00000001
# define CAMERA_ROTATION		0x00000002
# define CAMERA_FOV				0x00000004
# define CAMERA_ALL				0x00000007

# define LIGHT_TRANSLATION		0x00000010

# define PLANE_TRANSLATION		0x00000100
# define PLANE_ROTATION			0x00000200
# define PLANE_ALL				0x00000300

# define SPHERE_TRANSLATION		0x00001000
# define SPHERE_RADIUS			0x00002000
# define SPHERE_ALL				0x00003000

# define CYLINDER_TRANSLATION	0x00010000
# define CYLINDER_ROTATION		0x00020000
# define CYLINDER_RADIUS		0x00040000
# define CYLINDER_HEIGHT		0x00080000
# define CYLINDER_ALL			0x000F0000

# define CONE_TRANSLATION		0x00100000
# define CONE_ROTATION			0x00200000
# define CONE_RADIUS			0x00400000
# define CONE_HEIGHT			0x00800000
# define CONE_ALL				0x00F00000

# define SPOT_LIGHT_TRANSLATION	0x01000000
# define SPOT_LIGHT_ROTATION	0x02000000
# define SPOT_LIGHT_ANGLE		0x04000000
# define SPOT_LIGHT_ALL			0x07000000

# define UPDATE_ALL				0xFFFFFFFF

/* Number of objects */

# define NB_OBJECTS				8
# define NB_BONUS				2

/* Translation, rotation & other factors */

# define TRANSLATION_FACTOR		0.05
# define ROTATION_FACTOR		0.01
# define FOV_FACTOR				0.05
# define RADIUS_FACTOR			0.05
# define HEIGHT_FACTOR			0.05
# define LIGHT_RATIO_FACTOR		0.01
# define PIXEL_RESOLUTION		15

/* Maths const */

# define PI_360					0.008726646259971647884618453842443064

/* Objects */
enum {
	TYPE_MAIN_LIGHT,
	TYPE_SPOT_LIGHT,
	TYPE_SPHERE,
	TYPE_PLANE,
	TYPE_CYLINDER,
	TYPE_CONE
};

/* Structures */

struct	s_scene;

typedef struct s_point
{
	double	x;
	double	y;
	double	z;
}	t_point;

typedef struct s_matrix
{
	t_point	a;
	t_point	b;
	t_point	c;
}	t_matrix;

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

typedef struct s_spot_light
{
	t_point	coord;
	t_point	relative_coord;
	t_point	direction;
	t_point	right;
	t_point	down;
	t_color	color;
	double	ratio;
	double	angle;
	double	cos_angle;
}	t_spot_light;

typedef struct s_sphere
{
	t_point	coord;
	t_point	relative_coord;
	t_point	front;
	t_point	right;
	t_point	down;
	t_color	color;
	double	radius;
	double	radius_2;
	double	value;
}	t_sphere;

typedef struct s_plane
{
	t_point	coord;
	t_point	normal;
	t_point	right;
	t_point	down;
	t_color	color;
	double	value;
}	t_plane;

typedef struct s_cylinder
{
	t_point	coord;
	t_point	relative_coord;
	t_point	direction;
	t_point	vector_semi_height;
	t_point	center_top;
	t_point	center_down;
	t_point	relative_center_top;
	t_point	relative_center_down;
	t_point	right;
	t_point	down;
	t_color	color;
	double	radius;
	double	radius_2;
	double	semi_height;
	double	semi_height_2;
	double	value;
	double	value_top;
	double	value_down;
	double	value_semi_height;
	double	value_quad;
}	t_cylinder;

typedef struct s_cone
{
	t_point	coord;
	t_point	relative_coord;
	t_point	direction;
	t_point	vector_height;
	t_point	center_base;
	t_point	relative_center_base;
	t_point	right;
	t_point	down;
	t_color	color;
	double	radius;
	double	radius_2;
	double	height;
	double	height_2;
	double	value;
	double	ratio;
	double	value_base;
	double	value_height;
	double	value_quad;
}	t_cone;

typedef struct s_object
{
	void			*object;
	struct s_color	(*get_color)(struct s_scene *, struct s_object *, \
						t_point, t_point);
	struct s_point	(*get_normal)(t_point, t_point, void *);
	double			(*intersect)(t_point, void *, t_point *);
	void			(*update)(struct s_scene *, void *, unsigned int);
	void			(*translation_relative)(int, struct s_scene *);
	void			(*rotation_relative)(int, struct s_scene *);
	void			(*translation_absolute)(struct s_scene *, t_point);
	void			(*rotation_absolute)(struct s_scene *, t_matrix);
	void			(*numpad_plus_minus)(int, struct s_scene *);
	void			(*scroll)(int, struct s_scene *);
	t_color			*color_bis;
	int				type;
	int				specular;
}	t_object;

typedef struct s_phong
{
	t_point		light_coord;
	t_point		normal;
	t_point		camera_ray;
	t_point		hit_point;
	t_point		light_ray;
	t_color		color;
	t_color		light_color;
	t_object	*object;
	t_light		*light;
	double		rgb[3];
	double		light_ratio;
	double		camera_ray_dist;
	double		light_ray_dist_2;
	double		dot_light_normal;
}	t_phong;

typedef struct s_scene
{
	t_point		window_corner;
	t_amb_light	*amb_light;
	t_camera	*camera;
	t_light		*light;
	t_list		*spot_lights;
	t_object	**objects;
	void		*mlx;
	void		*window;
	void		*image;
	char		*address;
	int			bpp;
	int			line_len;
	int			endian;
	int			width;
	int			height;
	int			index;
	int			nb_objects;
	int			mode;
}	t_scene;

/* utils */

void			quit(t_scene *scene);

int				print_error(int error_code, char *error_msg);

int				write_type(t_scene *scene);

void			write_point(t_point point, char *name);

void			write_info(t_scene *scene);

/* maths */

double			inv_sqrt(double d);

double			quad_solv(double a, double b, double c, double *x);

int				str_to_double(char *str, double *d, int last);

double			cos_rot(void);

double			cos_rot_1(void);

double			sin_rot(void);

double			n_sin_rot(void);

//double		dist_op(t_point o, t_point p);

t_point			new_point(double x, double y, double z);

double			distance_square(t_point a, t_point b);

t_point			add_vectors(t_point v1, t_point v2);

t_point			sub_vectors(t_point v1, t_point v2);

//double		norm_vector(t_point normal);

t_point			scalar_multi(double lambda, t_point vector);

double			vector_angle(t_point a, t_point b);

t_point			unit_dist(t_point a, t_point b);

t_point			reflection(t_point ray, t_point axis);

t_point			cross_product(t_point v1, t_point v2);

double			dot_product(t_point v1, t_point v2);

double			norm_square(t_point vector);

t_point			unit_vector(t_point vector);

t_point			get_projection_unit(t_point vector, t_point axis);

t_point			orthogonal_base(t_point vector, t_point *orthogonal);

t_matrix		new_matrix(t_point a, t_point b, t_point c);

t_point			matrix_vector_multi(t_matrix matrix, t_point vector);

t_matrix		matrix_rotation(t_point vector, double s);

/* objects */

void			update_scene(t_scene *scene, unsigned int flags);

void			ratio_amb_light(int key_code, t_scene *scene);

void			fov_camera(int mouse_code, t_scene *scene);

void			update_camera(t_scene *scene, unsigned int flags);

void			update_light(t_scene *scene, void *object, unsigned int flags);

void			ratio_main_light(int key_code, t_scene *scene);

void			update_spot_light(t_scene *scene, \
					void *object, unsigned int flags);

void			ratio_spot_light(int key_code, t_scene *scene);

void			angle_spot_light(int mouse_code, t_scene *scene);

void			update_sphere(t_scene *scene, void *object, unsigned int flags);

void			radius_sphere(int mouse_code, t_scene *scene);

void			update_plane(t_scene *scene, void *object, unsigned int flags);

void			update_cylinder(t_scene *scene, \
					void *object, unsigned int flags);

void			radius_cylinder(int mouse_code, t_scene *scene);

void			height_cylinder(int key_code, t_scene *scene);

void			update_cone(t_scene *scene, void *object, unsigned int flags);

void			radius_cone(int mouse_code, t_scene *scene);

void			height_cone(int key_code, t_scene *scene);

/* intersect */

double			intersect_light(t_point ray, void *object, t_point *origin);

double			intersect_spot_light(t_point ray, \
					void *object, t_point *origin);

double			intersect_sphere(t_point ray, void *object, t_point *origin);

double			intersect_plane(t_point ray, void *object, t_point *origin);

double			intersect_cylinder(t_point ray, void *object, t_point *origin);

double			intersect_cone(t_point ray, void *object, t_point *origin);

t_object		*find_intersect(t_scene *scene, t_point ray, \
					double *intersect, int *index);

/* print */

unsigned int	create_trgb(unsigned char t, unsigned char r, \
					unsigned char g, unsigned char b);

unsigned int	color_trgb(t_color color);

unsigned int	get_pixel_color(t_scene *scene, int x, int y);

unsigned char	color_get_t(unsigned int trgb);

unsigned char	color_get_r(unsigned int trgb);

unsigned char	color_get_g(unsigned int trgb);

unsigned char	color_get_b(unsigned int trgb);

t_color			get_color_light(t_scene *scene, t_object *object, \
					t_point hit_point, t_point normal);

t_color			get_color_spot_light(t_scene *scene, t_object *object, \
					t_point hit_point, t_point normal);

t_color			get_color_sphere(t_scene *scene, t_object *object, \
					t_point hit_point, t_point normal);

t_point			normal_sphere(t_point ray, t_point hit_point, void *object);

t_color			get_color_plane(t_scene *scene, t_object *object, \
					t_point hit_point, t_point normal);

t_point			normal_plane(t_point ray, t_point hit_point, void *object);

t_color			get_color_cylinder(t_scene *scene, t_object *object, \
					t_point hit_point, t_point normal);

t_point			normal_cylinder(t_point ray, t_point hit_point, void *object);

t_color			get_color_cone(t_scene *scene, t_object *object, \
					t_point hit_point, t_point normal);

t_point			normal_cone(t_point ray, t_point hit_point, void *object);

void			put_pixel(t_scene *scene, int x, int y, unsigned int color);

void			print_window(t_scene *scene, int offset);

void			phong_ambient(t_amb_light *amb_light, \
					t_color base, double *rgb);

void			phong_diffuse(t_phong *phong, double dot);

void			phong_specular(t_phong *phong, double specular);

/* rotations */

void			rotation(int key_code, t_scene *scene);

void			rotation_relative_camera(int key_code, t_scene *scene);

void			rotation_absolute_camera(t_scene *scene, t_matrix matrix);

void			rotation_relative_spot_light(int key_code, t_scene *scene);

void			rotation_absolute_spot_light(t_scene *scene, t_matrix matrix);

void			rotation_relative_plane(int key_code, t_scene *scene);

void			rotation_absolute_plane(t_scene *scene, t_matrix matrix);

void			rotation_relative_cylinder(int key_code, t_scene *scene);

void			rotation_absolute_cylinder(t_scene *scene, t_matrix matrix);

void			rotation_relative_cone(int key_code, t_scene *scene);

void			rotation_absolute_cone(t_scene *scene, t_matrix matrix);

/* translations */

void			translation(int key_code, t_scene *scene);

void			translation_relative_camera(int key_code, t_scene *scene);

void			translation_absolute_camera(t_scene *scene, t_point vector);

void			translation_absolute_light(t_scene *scene, t_point vector);

void			translation_relative_spot_light(int key_code, t_scene *scene);

void			translation_absolute_spot_light(t_scene *scene, t_point vector);

void			translation_absolute_sphere(t_scene *scene, t_point vector);

void			translation_relative_plane(int key_code, t_scene *scene);

void			translation_absolute_plane(t_scene *scene, t_point vector);

void			translation_relative_cylinder(int key_code, t_scene *scene);

void			translation_absolute_cylinder(t_scene *scene, t_point vector);

void			translation_relative_cone(int key_code, t_scene *scene);

void			translation_absolute_cone(t_scene *scene, t_point vector);

/* hooks */

int				is_key_translation(int key_code);

int				is_key_rotation(int key_code);

int				key_hook(int key_code, t_scene *scene);

int				mouse_hook(int mouse_code, int x, int y, t_scene *scene);

int				key_release(int key_code, t_scene *scene);

int				mouse_release(int mouse_code, int x, int y, t_scene *scene);

/* start */

char			*next_item(char *line);

int				parse_bonus(t_object *object, char *item);

int				parse_color(t_color *color, char *item);

int				parse_color_bonus(t_object *object, char *item);

int				parse_ratio(double *ratio, char *item);

int				parse_length(double *length, char *item, char *name, char half);

int				parse_angle(double *angle, char *item);

int				parse_specular(t_object *object, char *item);

char			*next_coord(char *item, char last);

int				parse_coord(t_point *coord, char *item);

int				parse_vector(t_point *vector, char *item, char unit);

int				parse_amb_light(t_scene *scene, t_list *current, \
					t_object *object);

int				parse_camera(t_scene *scene, t_list *current, \
					t_object *object);

int				parse_light(t_scene *scene, t_list *current, t_object *object);

int				parse_spot_light(t_scene *scene, t_list *current, \
					t_object *object);

int				parse_sphere(t_scene *scene, t_list *current, \
					t_object *object);

int				parse_plane(t_scene *scene, t_list *current, t_object *object);

int				parse_cylinder(t_scene *scene, t_list *current, \
					t_object *object);

int				parse_cone(t_scene *scene, t_list *current, t_object *object);

int				read_file(int argc, char **argv, t_list **objects);

int				init(int argc, char **argv, t_scene **scene);

#endif
