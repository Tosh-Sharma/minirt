/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshsharma <toshsharma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 15:55:38 by tsharma           #+#    #+#             */
/*   Updated: 2023/04/18 19:49:51 by toshsharma       ###   ########.fr       */
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
# include <stdarg.h>
# include <fcntl.h>
# include "libft/libft.h"
# include "get_next_line.h"
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <signal.h>

#define BUFFER_SIZE 1

typedef struct s_color
{
	int color[3];
}				t_color;

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
	int         fov;
}				t_camera;

typedef struct s_light
{
	t_vector	origin;
	float		brightness;
	int		    color[3];
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
	int		    color[3];
}				t_sphere;

typedef struct s_plane
{
	t_vector	center;
	t_vector	normal;
	int		    color[3];
}				t_plane;

typedef struct s_cylinder
{
	t_vector	center;
	t_vector	normal;
	float		diameter;
	float		height;
	int		    color[3];
}				t_cylinder;

typedef struct s_cone
{
	t_vector	center;
	t_vector	normal;
	float		angle;
	int		    color[3];
}				t_cone;

typedef struct s_rt
{
	t_ambient	*ambient;
	t_camera	camera;
	t_light		*light;
	t_sphere	*sphere;
	t_plane		*plane;
	t_cylinder	*cylinder;
	t_cone		*cone;
    unsigned int    ct_a;
    unsigned int    ct_c;
    unsigned int    ct_l;
    unsigned int    ct_sp;
    unsigned int    ct_cy;
    unsigned int    ct_pl;
    unsigned int    max_a;
    unsigned int    max_c;
    unsigned int    max_l;
    unsigned int    max_sp;
    unsigned int    max_cy;
    unsigned int    max_pl;
    int         file_fd;
    char        **split_line;
}				t_rt;


int		ft_find_index(char *str, int c);
char	*ft_gnl_strjoin(char *s1, char *s2);
char	*ft_gnl_extra(char *save);
char	*ft_get_line(char *save);
char	*ft_read(int fd, char *save);
char	*get_next_line(int fd);

#endif