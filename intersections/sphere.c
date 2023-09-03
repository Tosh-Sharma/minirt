/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshsharma <toshsharma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 16:49:28 by toshsharma        #+#    #+#             */
/*   Updated: 2023/09/03 11:30:35 by toshsharma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

double	min_num(double a, double b)
{
	if (a < b)
		return (a);
	return (b);
}

void	intersect_sphere(t_sphere sphere, t_ray ray, double *t)
{
	double	a;
	double	b;
	double	c;
	double	discriminant;
	double	new_t;

	a = 1;
	b = 2 * dot_product(ray.direction, vec_subtract(sphere.center,
				ray.origin));
	c = dot_product(vec_subtract(sphere.center, ray.origin),
			vec_subtract(sphere.center, ray.origin))
		- (powf(sphere.diameter / 2, 2));
	discriminant = sqrt(b) - (4 * a * c);
	if (discriminant < 0)
		return ;
	else
	{
		new_t = min_num((-b + sqrt(discriminant)) / (2 * a),
				(-b - sqrt(discriminant)) / (2 * a));
		if (new_t > 0 && new_t < *t)
		{
			*t = new_t;
		}
	}
}
