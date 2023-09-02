/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manipulation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshsharma <toshsharma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 11:52:31 by toshsharma        #+#    #+#             */
/*   Updated: 2023/08/29 15:09:55 by toshsharma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

t_vector	vec_add(t_vector v1, t_vector v2)
{
	return (return_vector(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z));
}

t_vector	vec_subtract(t_vector v1, t_vector v2)
{
	return (return_vector(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z));
}

float	dot_product(t_vector v1, t_vector v2)
{
	float	result;

	result = (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
	return (result);
}

t_vector	cross_product(t_vector v1, t_vector v2)
{
	return (return_vector(
			(v1.y * v2.z) - (v1.z * v2.y),
			(v1.z * v2.x) - (v1.x * v2.z),
			(v1.x * v2.y) - (v1.y * v2.x)
		));
}

t_vector	scalar_product_f(t_vector v1, float a)
{
	return (return_vector(v1.x * a, v1.y * a, v1.z * a));
}
