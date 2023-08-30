/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshsharma <toshsharma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 17:25:07 by toshsharma        #+#    #+#             */
/*   Updated: 2023/08/26 06:25:57 by toshsharma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

t_vector	return_vector(float x, float y, float z)
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
		++i;
	}
	vector = return_vector(x, y, z);
	return (vector);
}

t_vector	normalize_vector(t_vector v)
{
	float		denominator;

	denominator = sqrtf(dot_product(v, v));
	return (return_vector(v.x / denominator,
			v.y / denominator, v.z / denominator));
}
