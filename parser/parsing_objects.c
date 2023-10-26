/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_objects.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshsharma <toshsharma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 17:41:54 by toshsharma        #+#    #+#             */
/*   Updated: 2023/10/26 13:41:04 by toshsharma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

t_light	light(t_rt *rt)
{
	t_light	light;
	char	**split_origin;

	if (rt->split_line[4] != NULL)
		perror_and_exit("Extra light settings");
	split_origin = ft_split(rt->split_line[1], ',');
	triplets_checker(split_origin);
	light.origin = parse_input_as_vector(split_origin);
	free_strings(split_origin);
	light.brightness = ft_atod(rt->split_line[2]);
	if (light.brightness < 0.0 || light.brightness > 1.0)
		perror_and_exit("Unacceptable light brightness value");
	get_color_light(rt, &light);
	++rt->ct_l;
	if (rt->ct_l != 1)
		perror_and_exit("Mandatory parts requires 1 light only");
	return (light);
}

t_sphere	sphere(t_rt *rt)
{
	t_sphere	sphere;
	char		**split_center;

	if (rt->split_line[4] != NULL)
		perror_and_exit("Extra sphere settings");
	split_center = ft_split(rt->split_line[1], ',');
	triplets_checker(split_center);
	sphere.center = parse_input_as_vector(split_center);
	free_strings(split_center);
	sphere.diameter = ft_atod(rt->split_line[2]);
	if (sphere.diameter < 0.0)
		perror_and_exit("Unacceptable sphere diameter value");
	get_color_sphere(rt, &sphere);
	++rt->ct_sp;
	return (sphere);
}

t_plane	plane(t_rt *rt)
{
	t_plane	pl;
	char	**split_center;
	char	**split_normal;

	if (rt->split_line[4] != NULL)
		perror_and_exit("Extra plane settings");
	split_center = ft_split(rt->split_line[1], ',');
	triplets_checker(split_center);
	pl.center = parse_input_as_vector(split_center);
	free_strings(split_center);
	split_normal = ft_split(rt->split_line[2], ',');
	triplets_checker(split_normal);
	get_color_plane(rt, &pl, split_normal);
	++rt->ct_pl;
	return (pl);
}

t_cylinder	cylinder(t_rt *rt)
{
	t_cylinder	cy;
	char		**split_center;
	char		**split_normal;

	if (rt->split_line[6] != NULL)
		perror_and_exit("Extra cylinder settings");
	split_center = ft_split(rt->split_line[1], ',');
	triplets_checker(split_center);
	cy.center = parse_input_as_vector(split_center);
	free_strings(split_center);
	split_normal = ft_split(rt->split_line[2], ',');
	triplets_checker(split_normal);
	cy.normal = parse_input_as_vector(split_normal);
	free_strings(split_normal);
	if (cy.normal.x < -1.0 || cy.normal.x > 1.0 || cy.normal.y < -1.0
		|| cy.normal.y > 1.0 || cy.normal.z < -1.0 || cy.normal.z > 1.0)
		perror_and_exit("Unacceptable cylinder normal values");
	get_color_cylinder(rt, &cy);
	++rt->ct_cy;
	return (cy);
}

t_cone	cone(t_rt *rt)
{
	t_cone	co;
	char	**split_center;
	char	**split_normal;

	if (rt->split_line[6] != NULL)
		perror_and_exit("Extra cone settings");
	split_center = ft_split(rt->split_line[1], ',');
	if (split_center[3] != NULL)
	{
		free_strings(split_center);
		perror_and_exit("Unacceptable cone coordinates settings");
	}
	co.center = parse_input_as_vector(split_center);
	free_strings(split_center);
	split_normal = ft_split(rt->split_line[2], ',');
	if (split_normal[3] != NULL)
		perror_and_exit("Unacceptable cone normal settings");
	co.normal = parse_input_as_vector(split_normal);
	free_strings(split_normal);
	if (co.normal.x < -1.0 || co.normal.x > 1.0 || co.normal.y < -1.0
		|| co.normal.y > 1.0 || co.normal.z < -1.0 || co.normal.z > 1.0)
		perror_and_exit("Unacceptable cone normal values");
	get_color_cone(rt, &co);
	++rt->ct_co;
	return (co);
}
