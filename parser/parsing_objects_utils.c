/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_objects_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshsharma <toshsharma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 16:16:09 by toshsharma        #+#    #+#             */
/*   Updated: 2023/10/26 13:28:18 by toshsharma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

void	get_color_light(t_rt *rt, t_light *light)
{
	int		i;
	char	**split_color;

	split_color = ft_split(rt->split_line[3], ',');
	triplets_checker(split_color);
	i = -1;
	while (split_color[++i])
	{
		light->color[i] = ft_atoi_checker(split_color[i]);
		if (light->color[i] > 255 || light->color[i] < 0)
		{
			free_strings(split_color);
			perror_and_exit("Wrong light color value");
		}
	}
	free_strings(split_color);
}

void	get_color_sphere(t_rt *rt, t_sphere *sphere)
{
	int		i;
	char	**split_color;

	split_color = ft_split(rt->split_line[3], ',');
	triplets_checker(split_color);
	i = -1;
	while (split_color[++i])
	{
		sphere->color[i] = ft_atoi_checker(split_color[i]);
		if (sphere->color[i] > 255 || sphere->color[i] < 0)
		{
			free_strings(split_color);
			perror_and_exit("Wrong sphere color value");
		}
	}
	free_strings(split_color);
}

void	get_color_plane(t_rt *rt, t_plane *plane, char **split_normal)
{
	char	**split_color;
	int		i;

	plane->normal = parse_input_as_vector(split_normal);
	free_strings(split_normal);
	if (plane->normal.x < -1.0 || plane->normal.x > 1.0
		|| plane->normal.y < -1.0 || plane->normal.y > 1.0
		|| plane->normal.z < -1.0 || plane->normal.z > 1.0)
		perror_and_exit("Unacceptable plane normal values");
	split_color = ft_split(rt->split_line[3], ',');
	triplets_checker(split_color);
	i = -1;
	while (split_color[++i])
	{
		plane->color[i] = ft_atoi_checker(split_color[i]);
		if (plane->color[i] > 255 || plane->color[i] < 0)
			perror_and_exit("Wrong plane color value");
	}
	free_strings(split_color);
}

void	get_color_cylinder(t_rt *rt, t_cylinder *cylinder)
{
	char		**split_color;
	int			i;

	cylinder->diameter = ft_atod(rt->split_line[3]);
	if (cylinder->diameter < 0.0)
		perror_and_exit("Unacceptable cylinder diameter value");
	cylinder->height = ft_atod(rt->split_line[4]);
	if (cylinder->height < 0.0)
		perror_and_exit("Unacceptable cylinder height value");
	split_color = ft_split(rt->split_line[5], ',');
	triplets_checker(split_color);
	i = -1;
	while (split_color[++i])
	{
		cylinder->color[i] = ft_atoi_checker(split_color[i]);
		if (cylinder->color[i] > 255 || cylinder->color[i] < 0)
		{
			free_strings(split_color);
			perror_and_exit("Wrong cylinder color value");
		}
	}
	free_strings(split_color);
}

void	get_color_cone(t_rt *rt, t_cone *cone)
{
	char		**split_color;
	int			i;

	cone->diameter = ft_atod(rt->split_line[3]);
	if (cone->diameter < 0.0)
		perror_and_exit("Unacceptable cone diameter value");
	cone->height = ft_atod(rt->split_line[4]);
	if (cone->height < 0.0)
		perror_and_exit("Unacceptable cone height value");
	split_color = ft_split(rt->split_line[5], ',');
	if (split_color[3] != NULL)
		perror_and_exit("Unacceptable cone color settings");
	i = -1;
	while (split_color[++i])
	{
		cone->color[i] = ft_atoi_checker(split_color[i]);
		if (cone->color[i] > 255 || cone->color[i] < 0)
		{
			free_strings(split_color);
			perror_and_exit("Wrong cone color value");
		}
	}
	free_strings(split_color);
}
