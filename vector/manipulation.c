/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manipulation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshsharma <toshsharma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 11:52:31 by toshsharma        #+#    #+#             */
/*   Updated: 2023/08/16 12:26:53 by toshsharma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

t_vector	vec_add(t_vector v1, t_vector v2)
{
	t_vector	result;

	result.x = v1.x + v2.x;
	result.y = v1.y + v2.y;
	result.z = v1.z + v2.z;
	return (result);
}

t_vector	vec_subtract(t_vector v1, t_vector v2)
{
	t_vector	result;

	result.x = v1.x - v2.x;
	result.y = v1.y - v2.y;
	result.z = v1.z - v2.z;
	return (result);
}

float	dot_product(t_vector v1, t_vector v2)
{
	float	result;

	result = (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
	return (result);
}

t_vector	cross_product(t_vector v1, t_vector v2)
{
	t_vector	result;

	result.x = (v1.y * v2.z) - (v1.z * v2.y);
	result.y = (v1.z * v2.x) - (v1.x * v2.z);
	result.z = (v1.x * v2.y) - (v1.y * v2.x);
	return (result);
}

t_vector	scalar_float_product(t_vector v1, float a)
{
	t_vector	result;

	result.x = v1.x * a;
	result.y = v1.y * a;
	result.z = v1.z * a;
	return (result);
}

// t_vector	scalar_int_product(t_vector v1, int a)
// {
// 	t_vector	result;

// 	result.x = v1.x * a;
// 	result.y = v1.y * a;
// 	result.z = v1.z * a;
// 	return (result);
// }
