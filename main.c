/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshsharma <toshsharma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 16:04:58 by tsharma           #+#    #+#             */
/*   Updated: 2023/04/04 11:58:17 by toshsharma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_rt	g_rt;

void	my_exit(t_rt *rt)
{
	free(rt);
	exit(0);
}

void	perror_and_exit(char *input)
{
	perror(input);
	exit(0);
}

char	*get_next_line(int fd)
{
    int     i = 0;
    int     rd = 0;
    char    character;
    char    *buffer = malloc(100000);

    while ((rd = read(fd, &character, 1)) > 0)
    {
        buffer[i++] = character;
        if (character == '\n')
            break ;
    }
    buffer[i] = '\0';
    if (rd == -1 || i == 0 || (!buffer[i - 1] && !rd))
        return (free(buffer), NULL);
    return(buffer);
}

void	free_strings(char **str)
{
	int	i;

	i = -1;
	while (str != NULL && str[++i] != NULL)
		free(str[i]);
	free(str);
	str = NULL;
}

t_vector	return_vector(float x, float y, float z)
{
	t_vector	vector;

	vector.x = x;
	vector.y = y;
	vector.z = z;
	return (vector);
}

float	ft_atof(const char *str)
{
	double	res;
	double	res2;
	char	*c;
	int		len;

	c = (char *)str;
	res = (double)ft_atoi(c);
	while (*c && *c != '.')
		c++;
	if (*c == '.')
		c++;
	res2 = (double)ft_atoi(c);
	len = ft_strlen(c);
	while (len--)
		res2 /= 10;
	if (res >= 0)
		return ((float)(res + res2));
	else
		return ((float)(res - res2));
}

t_vector	parse_input_as_vector(char	**splitted_line)
{
	int			i;
	float		x;
	float		y;
	float		z;
	t_vector	vector;

	i = 0;
	while (splitted_line[i])
	{
		if (i == 0)
			x = ft_atof(splitted_line[i]);
		else if (i == 1)
			y = ft_atof(splitted_line[i]);
		else if (i == 2)
			z = ft_atof(splitted_line[i]);
		i++;
	}
	vector = return_vector(x, y, z);
	return (vector);
}

t_ambient	ambient_lightning(t_rt *rt)
{
	t_ambient	ambient;
	char		**split_color;
	int			i;

	if (rt->split_line[3] != NULL)
		perror_and_exit("Extra ambient lightning settings");
	ambient.brightness = ft_atof(rt->split_line[1]);
	if (ambient.brightness > 1.0 || ambient.brightness < 0.0)
		perror_and_exit("Unacceptable ambient brightness value");
	split_color = ft_split(rt->split_line[2], ',');
	if (split_color[3] != NULL)
		perror_and_exit("Unacceptable ambient color values");
	i = -1;
	while (split_color[++i])
	{
		ambient.color[i] = ft_atoi(split_color[i]);
		if (ambient.color[i] > 255 || ambient.color[i] < 0)
			perror_and_exit("Wrong ambient lightning color value");
	}
	free_strings(split_color);
	++rt->ct_a;
	//else QUOI FAIRE?
	return (ambient);
}

void	camera(t_rt *rt)
{
	char		**split_origin;
	char		**split_direction;

	if (rt->split_line[4] != NULL)
		perror_and_exit("Extra camera settings");
	split_origin = ft_split(rt->split_line[1], ',');
	if (split_origin[3] != NULL)
		perror_and_exit("Unacceptable camera position settings");
	rt->camera.origin = parse_input_as_vector(split_origin);
	printf("x = %f\n", rt->camera.origin.x);
	printf("y = %f\n", rt->camera.origin.y);
	printf("z = %f\n", rt->camera.origin.z);
	free_strings(split_origin);
	split_direction = ft_split(rt->split_line[2], ',');
	if (split_direction[3] != NULL)
		perror_and_exit("Unacceptable camera orientation settings");
	rt->camera.direction = parse_input_as_vector(split_direction);
	printf("x = %f\n", rt->camera.direction.x);
	printf("y = %f\n", rt->camera.direction.y);
	printf("z = %f\n", rt->camera.direction.z);
	free_strings(split_direction);
	if ((rt->camera.direction.x > 1.0 || rt->camera.direction.x < -1.0)
		|| (rt->camera.direction.y > 1.0 || rt->camera.direction.y < -1.0)
		|| (rt->camera.direction.z > 1.0 || rt->camera.direction.z < -1.0))
		perror_and_exit("Unacceptable orientation vector values");
	rt->camera.fov = ft_atoi(rt->split_line[3]);
	printf("camera fov = %d\n", rt->camera.fov);
	if (rt->camera.fov < 0 || rt->camera.fov > 180)
		perror_and_exit("Unacceptable camera fov value");
}

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
	line = NULL;
	while ((line = get_next_line(rt->file_fd)) != NULL)
	{
		printf("line :%s\n", line);
		rt->split_line = ft_split(line, ' ');
		free(line);
		if (!flag)
			parser_counter(rt);
		else
			parser(rt);
		free_strings(rt->split_line);
	}
	close(rt->file_fd);
	printf("\n-----COUNTER-----\nA = %d\nC = %d\nL = %d\nSP = %d\nPL = %d\nCY = %d\n", rt->max_a, rt->max_c, rt->max_l, rt->max_sp, rt->max_pl, rt->max_cy);
}

void	init_parse(t_rt *rt, char *file)
{
	int	i;

	i = 0;
	while (file[i] && file[i] != '.')
		++i;
	if (file[i + 1] != 'r' || file[i + 2] != 't' || file[i + 3] != '\0')
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

int	main(int argc, char **argv)
{
	if (argc != 2)
		perror_and_exit("Unacceptable number of arguments");
	init_parse(&g_rt, argv[1]);
}
