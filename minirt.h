/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshsharma <toshsharma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 15:55:38 by tsharma           #+#    #+#             */
/*   Updated: 2023/10/26 17:07:38 by toshsharma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

/*
** Libs
*/
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <stdarg.h>
# include <fcntl.h>
# include <stdbool.h>

# include "libft/libft.h"
# include "minilibx_opengl/mlx.h"

# define WIDTH 960
# define HEIGHT 800

typedef unsigned int	t_uint;

typedef struct s_color
{
	int	color[3];
}	t_color;

typedef struct s_vector
{
	double	x;
	double	y;
	double	z;
}				t_vector;

typedef struct s_camera
{
	t_vector	origin;
	t_vector	direction;
	int			fov;
	double		view;
}				t_camera;

typedef struct s_light
{
	t_vector	origin;
	double		brightness;
	int			color[3];
}				t_light;

typedef struct s_ambient
{
	double	brightness;
	int		color[3];
}				t_ambient;

// The x and y inside the ray are pointing to the viewport screen's coordinates.
// In order to color a pixel, we need to know the x and y of the pixel.
typedef struct s_ray
{
	t_vector	origin;
	t_vector	direction;
	int			x;
	int			y;
	t_vector	normal;
}				t_ray;

typedef struct s_sphere
{
	t_vector	center;
	double		diameter;
	int			color[3];
}				t_sphere;

typedef struct s_plane
{
	t_vector	center;
	t_vector	normal;
	int			color[3];
}				t_plane;

typedef struct s_cylinder
{
	t_vector	center;
	t_vector	normal;
	double		diameter;
	double		height;
	int			color[3];
}				t_cylinder;

typedef struct s_disk
{
	t_vector	center;
	t_vector	normal;
	double		diameter;
	int			color[3];
}			t_disk;

typedef struct s_cone
{
	t_vector	center;
	t_vector	normal;
	double		height;
	double		diameter;
	int			color[3];
}				t_cone;

typedef struct s_data {
	void		*img;
	char		*addr;
	int			line_length;
	int			bits_per_pixel;
	int			endian;
	void		*mlx;
	void		*mlx_win;
	t_vector	forward;
	t_vector	up;
	t_vector	right;
	t_vector	up_guide;
	t_vector	upper_left;
	t_vector	pixel_delta_u;
	t_vector	pixel_delta_v;
	double		width;
	double		height;
	double		img_width;
	double		img_height;
	double		img_aspect_ratio;
	double		scale;
}	t_image;

typedef struct s_rt
{
	t_ambient	*ambient;
	t_camera	camera;
	t_light		*light;
	t_sphere	*sphere;
	t_plane		*plane;
	t_cylinder	*cylinder;
	t_cone		*cone;
	t_uint		ct_a;
	t_uint		ct_c;
	t_uint		ct_l;
	t_uint		ct_sp;
	t_uint		ct_pl;
	t_uint		ct_cy;
	t_uint		ct_co;
	t_uint		max_a;
	t_uint		max_c;
	t_uint		max_l;
	t_uint		max_sp;
	t_uint		max_cy;
	t_uint		max_pl;
	t_uint		max_cone;
	int			cam_inside;
	int			light_inside;
	int			file_fd;
	char		**split_line;
	t_image		img;
	t_ray		ray;
	double		*t;
	t_ambient	background;
	t_ambient	black;
}				t_rt;

typedef struct s_quadratic
{
	double	a;
	double	b;
	double	c;
	double	determinant;
	double	t1;
	double	t2;
	double	*t;
}		t_quadratic;

typedef struct s_cone_solver
{
	t_vector	v;
	t_vector	w;
	t_vector	h;
	double		m;
}	t_cone_solver;

/**	Function definitions	*/
t_light		light(t_rt *rt);
t_cylinder	cylinder(t_rt *rt);
t_plane		plane(t_rt *rt);
t_sphere	sphere(t_rt *rt);
t_cone		cone(t_rt *rt);

void		camera(t_rt *rt);
t_ambient	ambient_lightning(t_rt *rt);

void		init_parse(t_rt *rt, char *file);

int			exit_hook(t_rt *rt);
int			key_hook(int keycode, t_rt *rt);
void		my_exit(t_rt *rt);
void		perror_and_exit(char *input);
void		free_strings(char **str);
double		ft_atod(const char *str);
int			ft_atoi_checker(char *str);

t_vector	vectorize(double x, double y, double z);
t_vector	parse_input_as_vector(char	**splitted_line);
t_vector	vec_add(t_vector v1, t_vector v2);
t_vector	vec_subtract(t_vector v1, t_vector v2);
t_vector	cross_product(t_vector v1, t_vector v2);
double		dot(t_vector v1, t_vector v2);
t_vector	scalar_product(t_vector v1, double a);
t_vector	normalize_vector(t_vector v);
double		vec_magnitude(t_vector v);

void		triplets_checker(char **triple);
void		get_color_light(t_rt *rt, t_light *light);
void		get_color_sphere(t_rt *rt, t_sphere *sphere);
void		get_color_plane(t_rt *rt, t_plane *plane, char **split_normal);
void		get_color_cylinder(t_rt *rt, t_cylinder *cylinder);
void		get_color_cone(t_rt *rt, t_cone *co);

void		print_vector(t_vector v, char *str);
double		min_num(double a, double b);
double		max_num(double a, double b);
int			clamp(int n, int min, int max);

void		copy_colors(int *color_src, int *color_dest);
int			array_to_int(int c[3], double a);
int			add_two_colors(int c1[3], double a, int c2[3], double b);
int			add_hex_colors(int c1, int c2);
int			multiply_light(int pixel_point, int light[3]);
int			multiply_hex_colors(int c1, int c2);
int			c_c(t_rt *rt, int input_color[3], double lam_ref, double spec);

void		ray_tracing(t_rt *rt);
void		cast_rays(t_rt *rt);
void		iterate_over_objects(t_rt *rt, t_ray ray, double *t);
void		set_up_vector_directions(t_rt *rt);
void		put_pixel(t_image *data, int x, int y, int color);

double		generate_shadow_ray(t_rt *rt, t_ray ray, t_vector light, double *t);
double		solve_shadow_for_t(t_cylinder cylinder, t_ray ray,
				t_quadratic *quad);

double		intersect_shadow_cylinder(t_cylinder cylinder, t_ray ray,
				double *t);
double		intersect_shadow_disk(t_disk disk, t_ray ray, double *t);
double		handle_shadow_disks(t_cylinder cylinder, t_ray ray, double *t);
double		solve_shadow_for_t(t_cylinder cylinder, t_ray ray,
				t_quadratic *quad);
double		intersect_shadow_plane(t_plane plane, t_ray ray, double *t);
double		intersect_shadow_sphere(t_sphere sphere, t_ray ray, double *t);
double		intersect_shadow_cone(t_cone cone, t_ray ray, double *t);

void		handle_disks(t_rt *rt, t_cylinder cylinder, t_ray ray, double *t);
void		intersect_sphere(t_rt *rt, t_sphere sphere, t_ray ray, double *t);
void		intersect_plane(t_rt *rt, t_plane plane, t_ray ray, double *t);
void		intersect_cylinder(t_rt *rt, t_cylinder cylinder, t_ray ray,
				double *t);
void		solve_for_t(t_rt *rt, t_cylinder cylinder, t_ray ray,
				t_quadratic *quad);
double		check_for_m_in_range(t_quadratic *quad, t_cylinder cylinder,
				t_ray ray);
void		calculate_tube_pixel_color(t_rt *rt, t_cylinder cylinder, t_ray ray,
				double *t);
void		calculate_inside_tube_pixel_color(t_rt *rt, t_cylinder cylinder,
				t_ray ray, double *t);		
int			cam_inside_or_not(t_rt *rt, t_cylinder cylinder);
int			light_inside_or_not(t_rt *rt, t_cylinder cylinder);
void		intersect_disk(t_rt *rt, t_disk disk, t_ray ray, double *t);
void		intersect_cone(t_rt *rt, t_cone cone, t_ray ray, double *t);
double		dist(t_rt *rt, t_vector light);
double		spec(t_rt *rt, t_vector normal, t_ray ray, double *t);

#endif