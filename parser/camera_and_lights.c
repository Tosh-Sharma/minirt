/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_and_lights.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshsharma <toshsharma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 17:44:10 by toshsharma        #+#    #+#             */
/*   Updated: 2023/10/08 18:56:47 by toshsharma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

void	triplets_checker(char **triple)
{
	int	i;

	i = 0;
	while (triple[i])
		i++;
	if (i != 3)
	{
		free_strings(triple);
		perror_and_exit("wrong set of values");
	}
}

int	ft_atoi_checker(char *str)
{
	int	value;
	int	i;
	int	max;

	i = -1;
	max = ft_strlen(str);
	while (++i < max)
	{
		if ((str[i] < 48 || str[i] > 57) && str[i] != 10)
			perror_and_exit("wrong int value");
	}
	value = ft_atoi(str);
	return (value);
}

t_ambient	ambient_lightning(t_rt *rt)
{
	t_ambient	ambient;
	char		**split_color;
	int			i;

	if (rt->split_line[3] != NULL)
		perror_and_exit("Extra ambient lightning settings");
	ambient.brightness = ft_atod(rt->split_line[1]);
	if (ambient.brightness > 1.0 || ambient.brightness <= 0.0)
		perror_and_exit("Unacceptable ambient brightness value");
	split_color = ft_split(rt->split_line[2], ',');
	triplets_checker(split_color);
	i = -1;
	while (split_color[++i])
	{
		ambient.color[i] = ft_atoi_checker(split_color[i]);
		if (ambient.color[i] > 255 || ambient.color[i] < 0)
			perror_and_exit("Wrong ambient lightning color value");
	}
	free_strings(split_color);
	++rt->ct_a;
	return (ambient);
}

void	camera(t_rt *rt)
{
	char		**split_origin;
	char		**split_direction;

	if (rt->split_line[4] != NULL)
		perror_and_exit("Extra camera settings");
	split_origin = ft_split(rt->split_line[1], ',');
	triplets_checker(split_origin);
	rt->camera.origin = parse_input_as_vector(split_origin);
	free_strings(split_origin);
	split_direction = ft_split(rt->split_line[2], ',');
	triplets_checker(split_direction);
	rt->camera.direction = parse_input_as_vector(split_direction);
	free_strings(split_direction);
	if ((rt->camera.direction.x > 1.0 || rt->camera.direction.x < -1.0)
		|| (rt->camera.direction.y > 1.0 || rt->camera.direction.y < -1.0)
		|| (rt->camera.direction.z > 1.0 || rt->camera.direction.z < -1.0))
		perror_and_exit("Unacceptable orientation vector values");
	rt->camera.fov = ft_atoi_checker(rt->split_line[3]);
	if (rt->camera.fov < 0 || rt->camera.fov > 180)
		perror_and_exit("Unacceptable camera fov value");
}
