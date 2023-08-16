/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshsharma <toshsharma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 15:55:38 by tsharma           #+#    #+#             */
/*   Updated: 2023/08/16 14:34:34 by toshsharma       ###   ########.fr       */
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

# define WIDTH 800
# define HEIGHT 600

typedef unsigned int	t_uint;

typedef struct s_color
{
	int	color[3];
}	t_color;

typedef struct s_vector
{
	float	x;
	float	y;
	float	z;
}				t_vector;

typedef struct s_camera
{
	t_vector	origin;
	t_vector	direction;
	int			fov;
}				t_camera;

typedef struct s_light
{
	t_vector	origin;
	float		brightness;
	int			color[3];
}				t_light;

typedef struct s_ambient
{
	float	brightness;
	int		color[3];
}				t_ambient;

typedef struct s_ray
{
	t_vector	origin;
	t_vector	direction;
}				t_ray;

typedef struct s_sphere
{
	t_vector	center;
	float		diameter;
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
	float		diameter;
	float		height;
	int			color[3];
}				t_cylinder;

typedef struct s_cone
{
	t_vector	center;
	t_vector	normal;
	float		angle;
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
	t_uint		ct_cy;
	t_uint		ct_pl;
	t_uint		max_a;
	t_uint		max_c;
	t_uint		max_l;
	t_uint		max_sp;
	t_uint		max_cy;
	t_uint		max_pl;
	int			file_fd;
	char		**split_line;
	t_image		img;
}				t_rt;

/**	Function definitions	*/
t_light		light(t_rt *rt);
t_cylinder	cylinder(t_rt *rt);
t_plane		plane(t_rt *rt);
t_sphere	sphere(t_rt *rt);

void		camera(t_rt *rt);
t_ambient	ambient_lightning(t_rt *rt);

void		init_parse(t_rt *rt, char *file);

void		my_exit(t_rt *rt);
void		perror_and_exit(char *input);
void		free_strings(char **str);
float		ft_atof(const char *str);

t_vector	return_vector(float x, float y, float z);
t_vector	parse_input_as_vector(char	**splitted_line);
t_vector	vec_add(t_vector v1, t_vector v2);
t_vector	vec_subtract(t_vector v1, t_vector v2);
t_vector	cross_product(t_vector v1, t_vector v2);
float		dot_product(t_vector v1, t_vector v2);
t_vector	scalar_float_product(t_vector v1, float a);
t_vector	normalize_vector(t_vector v);

void		ray_tracing(t_rt *rt);
void		cast_rays(t_rt *rt);
int			exit_hook(t_image *img);
void		put_pixel(t_image *data, int x, int y, int color);

#endif