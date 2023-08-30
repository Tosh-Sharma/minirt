/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshsharma <toshsharma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 16:49:28 by toshsharma        #+#    #+#             */
/*   Updated: 2023/08/28 09:29:12 by toshsharma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

void	intersect_sphere(t_sphere sphere, t_ray ray, float *t)
{
	float	a;
	float	b;
	float	c;
	float	discriminant;

	a = 1;
	b = 2 * dot_product(ray.direction, vec_subtract(ray.origin,
				sphere.center));
	c = dot_product(vec_subtract(ray.origin, sphere.center),
			vec_subtract(ray.origin, sphere.center))
		- (powf(sphere.diameter / 2, 2));
	discriminant = sqrt(b) - (4 * a * c);
	if (discriminant < 0)
		return ;
	else
	{
		*t = min((-b + sqrt(discriminant)) / (2 * a),
				(-b - sqrt(discriminant)) / (2 * a));
	}
}

float	min(float a, float b)
{
	if (a < b)
		return (a);
	return (b);
}
