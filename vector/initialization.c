/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshsharma <toshsharma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 17:25:07 by toshsharma        #+#    #+#             */
/*   Updated: 2023/10/26 16:22:36 by toshsharma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

// This function converts the input into a vector OR it 'vectorizes' the input
t_vector	vectorize(double x, double y, double z)
{
	t_vector	vector;

	vector.x = x;
	vector.y = y;
	vector.z = z;
	return (vector);
}

t_vector	parse_input_as_vector(char	**splitted_line)
{
	int			i;
	double		x;
	double		y;
	double		z;
	t_vector	vector;

	i = 0;
	while (splitted_line[i])
	{
		if (i == 0)
			x = ft_atod(splitted_line[i]);
		else if (i == 1)
			y = ft_atod(splitted_line[i]);
		else if (i == 2)
			z = ft_atod(splitted_line[i]);
		++i;
	}
	vector = vectorize(x, y, z);
	return (vector);
}

t_vector	normalize_vector(t_vector v)
{
	double		denominator;

	denominator = sqrt(dot(v, v));
	return (vectorize(v.x / denominator,
			v.y / denominator, v.z / denominator));
}

void	print_vector(t_vector v, char *str)
{
	printf("%s vector is x: %f, y: %f, z: %f\n", str, v.x, v.y, v.z);
}
