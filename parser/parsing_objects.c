/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_objects.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshsharma <toshsharma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 17:41:54 by toshsharma        #+#    #+#             */
/*   Updated: 2023/08/16 16:42:58 by toshsharma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

t_light	light(t_rt *rt) //rt->light[index of which light we are talking about]->...
{
	t_light	light;
	char	**split_origin;
	char	**split_color;
	int		i;

	if (rt->split_line[4] != NULL)
		perror_and_exit("Extra light settings");
	split_origin = ft_split(rt->split_line[1], ',');
	if (split_origin[3] != NULL)
		perror_and_exit("Unacceptable light coordinates settings");
	light.origin = parse_input_as_vector(split_origin);
	free_strings(split_origin);
	light.brightness = ft_atof(rt->split_line[2]);
	if (light.brightness < 0.0 || light.brightness > 1.0)
		perror_and_exit("Unacceptable light brightness value");
	split_color = ft_split(rt->split_line[3], ',');
	if (split_color[3] != NULL)
		perror_and_exit("Unacceptable light color settings");
	i = -1;
	while (split_color[++i])
	{
		light.color[i] = ft_atoi(split_color[i]);
		if (light.color[i] > 255 || light.color[i] < 0)
			perror_and_exit("Wrong light color value");
	}
	++rt->ct_l;
	return (light);
}

t_sphere	sphere(t_rt *rt)
{
	t_sphere	sphere;
	char		**split_center;
	char		**split_color;
	int			i;

	if (rt->split_line[4] != NULL)
		perror_and_exit("Extra sphere settings");
	split_center = ft_split(rt->split_line[1], ',');
	if (split_center[3] != NULL)
		perror_and_exit("Unacceptable sphere coordinates settings");
	sphere.center = parse_input_as_vector(split_center);
	free_strings(split_center);
	sphere.diameter = ft_atof(rt->split_line[2]);
	if (sphere.diameter < 0.0)
		perror_and_exit("Unacceptable sphere diameter value");
	split_color = ft_split(rt->split_line[3], ',');
	if (split_color[3] != NULL)
		perror_and_exit("Unacceptable sphere coordinates settings");
	i = -1;
	while (split_color[++i])
	{
		sphere.color[i] = ft_atoi(split_color[i]);
		if (sphere.color[i] > 255 || sphere.color[i] < 0)
			perror_and_exit("Wrong sphere color value");
	}
	free_strings(split_color);
	++rt->ct_sp;
	return (sphere);
}

t_plane	plane(t_rt *rt)
{
	t_plane	plane;
	char	**split_center;
	char	**split_normal;
	char	**split_color;
	int		i;

	if (rt->split_line[4] != NULL)
		perror_and_exit("Extra plane settings");
	split_center = ft_split(rt->split_line[1], ',');
	if (split_center[3] != NULL)
		perror_and_exit("Unacceptable plane coordinates settings");
	plane.center = parse_input_as_vector(split_center);
	free_strings(split_center);
	split_normal = ft_split(rt->split_line[2], ',');
	if (split_normal[3] != NULL)
		perror_and_exit("Unacceptable plane normal settings");
	plane.normal = parse_input_as_vector(split_normal);
	free_strings(split_normal);
	if (plane.normal.x < -1.0 || plane.normal.x > 1.0 || plane.normal.y < -1.0
		|| plane.normal.y > 1.0 || plane.normal.z < -1.0 || plane.normal.z > 1.0)
		perror_and_exit("Unacceptable plane normal values");
	split_color = ft_split(rt->split_line[3], ',');
	if (split_color[3] != NULL)
		perror_and_exit("Unacceptable plane color settings");
	i = -1;
	while (split_color[++i])
	{
		plane.color[i] = ft_atoi(split_color[i]);
		if (plane.color[i] > 255 || plane.color[i] < 0)
			perror_and_exit("Wrong plane color value");
	}
	free_strings(split_color);
	++rt->ct_pl;
	return (plane);
}

t_cylinder	cylinder(t_rt *rt)
{
	t_cylinder	cylinder;
	char		**split_center;
	char		**split_normal;
	char		**split_color;
	int			i;

	if (rt->split_line[6] != NULL)
		perror_and_exit("Extra cylinder settings");
	split_center = ft_split(rt->split_line[1], ',');
	if (split_center[3] != NULL)
		perror_and_exit("Unacceptable cylinder coordinates settings");
	cylinder.center = parse_input_as_vector(split_center);
	free_strings(split_center);
	split_normal = ft_split(rt->split_line[2], ',');
	if (split_normal[3] != NULL)
		perror_and_exit("Unacceptable cylinder normal settings");
	cylinder.normal = parse_input_as_vector(split_normal);
	free_strings(split_normal);
	if (cylinder.normal.x < -1.0 || cylinder.normal.x > 1.0 || cylinder.normal.y < -1.0
		|| cylinder.normal.y > 1.0 || cylinder.normal.z < -1.0 || cylinder.normal.z > 1.0)
		perror_and_exit("Unacceptable cylinder normal values");
	cylinder.diameter = ft_atof(rt->split_line[3]);
	if (cylinder.diameter < 0.0)
		perror_and_exit("Unacceptable cylinder diameter value");
	cylinder.height = ft_atof(rt->split_line[4]); //CAN IT BE MINUS?
	if (cylinder.height < 0.0)
		perror_and_exit("Unacceptable cylinder height value");
	split_color = ft_split(rt->split_line[5], ',');
	if (split_color[3] != NULL)
		perror_and_exit("Unacceptable cylinder color settings");
	i = -1;
	while (split_color[++i])
	{
		cylinder.color[i] = ft_atoi(split_color[i]);
		if (cylinder.color[i] > 255 || cylinder.color[i] < 0)
			perror_and_exit("Wrong cylinder color value");
	}
	free_strings(split_color);
	++rt->ct_cy;
	return (cylinder);
}

// TODO: Do the required parsing for a Cone.
t_cone	cone(t_rt *rt)
{
	t_cone	cone;

	return (cone);
}