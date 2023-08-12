/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshsharma <toshsharma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 17:08:22 by toshsharma        #+#    #+#             */
/*   Updated: 2023/08/12 12:58:36 by toshsharma       ###   ########.fr       */
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
	else if (ft_strcmp(rt->split_line[0], "pl"))
		rt->max_pl += 1;
	else if (ft_strcmp(rt->split_line[0], "cy"))
		rt->max_cy += 1;
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
		printf("line :%s\n", line);
		rt->split_line = ft_split(line, ' ');
		free(line);
		if (!flag)
			parser_counter(rt);
		else
			parser(rt);
		free_strings(rt->split_line);
		line = get_next_line(rt->file_fd);
	}
	close(rt->file_fd);
	printf("\n-----COUNTER-----\nA = %d\nC = %d\nL = %d\nSP = %d\n \
		PL = %d\nCY = %d\n", rt->max_a, rt->max_c, rt->max_l, rt->max_sp, rt->max_pl, rt->max_cy);
}

void	init_parse(t_rt *rt, char *file)
{
	int	i;

	i = 0;
	while (file[i] && file[i] != '.')
		++i;
	if ((file[i + 1] != 'r') && (file[i + 2] != 't') && (file[i + 3] != '\0'))
		perror_and_exit("Unacceptable file extension");
	parse_file(rt, file, 0);
	if (rt->max_c != 1 || rt->max_a != 1)
		perror_and_exit("Only one camera and ambient lightning are allowed");
	rt->ambient = (t_ambient *)malloc(sizeof(t_ambient) * (rt->max_a + 1));
	rt->light = (t_light *)malloc(sizeof(t_light) * (rt->max_l + 1));
	rt->sphere = (t_sphere *)malloc(sizeof(t_sphere) * (rt->max_sp + 1));
	rt->plane = (t_plane *)malloc(sizeof(t_plane) * (rt->max_pl + 1));
	rt->cylinder = (t_cylinder *)malloc(sizeof(t_cylinder) * (rt->max_cy + 1));
	parse_file(rt, file, 1);
	i = -1;
	while (rt->ambient[++i].brightness)
		printf("\nAMBIENT[%d]\nBright = %f, red = %d, green = %d, blue = %d\n", i, rt->ambient[i].brightness, rt->ambient[i].color[0], rt->ambient[i].color[1], rt->ambient[i].color[2]);
	printf("\nCamera\nfov = %d, Origin(x = %f, y = %f, z = %f), Direction(x = %f, y = %f, z = %f)\n", rt->camera.fov, rt->camera.origin.x, rt->camera.origin.y, rt->camera.origin.z, rt->camera.direction.x, rt->camera.direction.y, rt->camera.direction.z);
	i = -1;
	while (rt->light[++i].brightness)
		printf("\nLIGHT[%d]\nBright = %f, x = %f, y = %f, z = %f, red = %d, green = %d, blue = %d\n", i, rt->light[i].brightness, rt->light[i].origin.x, rt->light[i].origin.y, rt->light[i].origin.z, rt->light[i].color[0], rt->light[i].color[1], rt->light[i].color[2]);
	i = -1;
	while (rt->sphere[++i].diameter)
		printf("\nSPHERE[%d]\nx = %f, y = %f, z = %f, diameter = %f, red = %d, green = %d, blue = %d\n", i, rt->sphere[i].center.x, rt->sphere[i].center.y, rt->sphere[i].center.z, rt->sphere[i].diameter, rt->sphere[i].color[0], rt->sphere[i].color[1], rt->sphere[i].color[2]);
	i = -1;
	while (rt->plane[++i].color[0])
		printf("\nPLANE[%d]\nCenter(x = %f, y = %f, z = %f), Normal(x = %f, y = %f, z = %f), red = %d, green = %d, blue = %d\n", i, rt->plane[i].center.x, rt->plane[i].center.y, rt->plane[i].center.z, rt->plane[i].normal.x, rt->plane[i].normal.y, rt->plane[i].normal.z, rt->sphere[i].color[0], rt->sphere[i].color[1], rt->sphere[i].color[2]);
	i = -1;
	while (rt->cylinder[++i].height)
		printf("\nCYLINDER[%d]\nCenter(x = %f, y = %f, z = %f), Normal(x = %f, y = %f, z = %f), diameter = %f, height = %f, red = %d, green = %d, blue = %d\n", i, rt->cylinder[i].center.x, rt->cylinder[i].center.y, rt->cylinder[i].center.z, rt->cylinder[i].normal.x, rt->cylinder[i].normal.y, rt->cylinder[i].normal.z, rt->cylinder[i].diameter, rt->cylinder[i].height, rt->cylinder[i].color[0], rt->cylinder[i].color[1], rt->cylinder[i].color[2]);
}

