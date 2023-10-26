/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshsharma <toshsharma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 17:08:22 by toshsharma        #+#    #+#             */
/*   Updated: 2023/10/26 13:45:36 by toshsharma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

void	parser_counter(t_rt *rt)
{
	if (ft_strcmp(rt->split_line[0], "A") == 0)
		rt->max_a += 1;
	else if (ft_strcmp(rt->split_line[0], "C") == 0)
		rt->max_c += 1;
	else if (ft_strcmp(rt->split_line[0], "L") == 0)
		rt->max_l += 1;
	else if (ft_strcmp(rt->split_line[0], "sp") == 0)
		rt->max_sp += 1;
	else if (ft_strcmp(rt->split_line[0], "pl") == 0)
		rt->max_pl += 1;
	else if (ft_strcmp(rt->split_line[0], "cy") == 0)
		rt->max_cy += 1;
	else if (ft_strcmp(rt->split_line[0], "co") == 0)
		rt->max_cone += 1;
	else
		perror_and_exit("Object identifier not recognisable");
}

void	parser(t_rt *rt)
{
	if (ft_strcmp(rt->split_line[0], "A") == 0)
		rt->ambient[rt->ct_a] = ambient_lightning(rt);
	else if (ft_strcmp(rt->split_line[0], "C") == 0)
		camera(rt);
	else if (ft_strcmp(rt->split_line[0], "L") == 0)
		rt->light[rt->ct_l] = light(rt);
	else if (ft_strcmp(rt->split_line[0], "sp") == 0)
		rt->sphere[rt->ct_sp] = sphere(rt);
	else if (ft_strcmp(rt->split_line[0], "pl") == 0)
		rt->plane[rt->ct_pl] = plane(rt);
	else if (ft_strcmp(rt->split_line[0], "cy") == 0)
		rt->cylinder[rt->ct_cy] = cylinder(rt);
	else if (ft_strcmp(rt->split_line[0], "co") == 0)
		rt->cone[rt->ct_co] = cone(rt);
	else
		perror_and_exit("Object identifier not recognisable");
}

void	init_values(t_rt *rt)
{
	rt->ct_a = 0;
	rt->ct_l = 0;
	rt->ct_sp = 0;
	rt->ct_cy = 0;
	rt->ct_pl = 0;
	rt->max_a = 0;
	rt->max_c = 0;
	rt->max_l = 0;
	rt->max_sp = 0;
	rt->max_cy = 0;
	rt->max_pl = 0;
}

void	parse_file(t_rt *rt, char *file, int flag)
{
	char	*line;

	rt->file_fd = open(file, O_RDONLY);
	if (rt->file_fd <= 0)
		perror_and_exit("File not found");
	if (!flag)
		init_values(rt);
	line = get_next_line(rt->file_fd);
	while (line != NULL)
	{
		rt->split_line = ft_split(line, ' ');
		free(line);
		if (!(ft_strcmp(rt->split_line[0], "#") == 0
				|| ft_strcmp(rt->split_line[0], "\n") == 0))
		{
			if (!flag)
				parser_counter(rt);
			else
				parser(rt);
		}
		free_strings(rt->split_line);
		line = get_next_line(rt->file_fd);
	}
	close(rt->file_fd);
}

void	init_parse(t_rt *rt, char *file)
{
	int	i;

	i = ft_strlen(file);
	if ((file[i - 1] != 't') || (file[i - 2] != 'r') || (file[i - 3] != '.'))
		perror_and_exit("Unacceptable file extension");
	parse_file(rt, file, 0);
	if (rt->max_c != 1 || rt->max_a != 1 || rt->max_l != 1)
		perror_and_exit("Only one camera and ambient lightning are allowed");
	rt->ambient = (t_ambient *)malloc(sizeof(t_ambient) * (rt->max_a + 1));
	rt->light = (t_light *)malloc(sizeof(t_light) * (rt->max_l + 1));
	rt->sphere = (t_sphere *)malloc(sizeof(t_sphere) * (rt->max_sp + 1));
	rt->plane = (t_plane *)malloc(sizeof(t_plane) * (rt->max_pl + 1));
	rt->cylinder = (t_cylinder *)malloc(sizeof(t_cylinder) * (rt->max_cy + 1));
	rt->cone = (t_cone *)malloc(sizeof(t_cone) * (rt->max_cone + 1));
	parse_file(rt, file, 1);
}
