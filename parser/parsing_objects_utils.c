#include "../minirt.h"

void	get_color_light(t_rt *rt, t_light *light)
{
	int		i;
	char	**split_color;

	split_color = ft_split(rt->split_line[3], ',');
	if (split_color[3] != NULL)
	{
		free_strings(split_color);
		perror_and_exit("Unacceptable light color settings");
	}
	i = -1;
	while (split_color[++i])
	{
		light->color[i] = ft_atoi(split_color[i]);
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
	if (split_color[3] != NULL)
	{
		free_strings(split_color);
		perror_and_exit("Unacceptable sphere coordinates settings");
	}
	i = -1;
	while (split_color[++i])
	{
		sphere->color[i] = ft_atoi(split_color[i]);
		if (sphere->color[i] > 255 || sphere->color[i] < 0)
		{
			free_strings(split_color);
			perror_and_exit("Wrong sphere color value");
		}
	}
	free_strings(split_color);
}

void	get_color_plane(t_rt *rt, t_plane *plane)
{
	char	**split_color;
	int		i;

	split_color = ft_split(rt->split_line[3], ',');
	if (split_color[3] != NULL)
		perror_and_exit("Unacceptable plane color settings");
	i = -1;
	while (split_color[++i])
	{
		plane->color[i] = ft_atoi(split_color[i]);
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
	if (split_color[3] != NULL)
		perror_and_exit("Unacceptable cylinder color settings");
	i = -1;
	while (split_color[++i])
	{
		cylinder->color[i] = ft_atoi(split_color[i]);
		if (cylinder->color[i] > 255 || cylinder->color[i] < 0)
		{
			free_strings(split_color);
			perror_and_exit("Wrong cylinder color value");
		}
	}
	free_strings(split_color);
}