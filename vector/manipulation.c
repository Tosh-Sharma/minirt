/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manipulation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshsharma <toshsharma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 11:52:31 by toshsharma        #+#    #+#             */
/*   Updated: 2023/10/26 16:22:36 by toshsharma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

t_vector	vec_add(t_vector v1, t_vector v2)
{
	return (vectorize(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z));
}

t_vector	vec_subtract(t_vector v1, t_vector v2)
{
	return (vectorize(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z));
}

double	dot(t_vector v1, t_vector v2)
{
	double	result;

	result = (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
	return (result);
}

t_vector	cross_product(t_vector v1, t_vector v2)
{
	return (vectorize(
			(v1.y * v2.z) - (v1.z * v2.y),
			(v1.z * v2.x) - (v1.x * v2.z),
			(v1.x * v2.y) - (v1.y * v2.x)
		));
}

t_vector	scalar_product(t_vector v1, double a)
{
	return (vectorize(v1.x * a, v1.y * a, v1.z * a));
}
