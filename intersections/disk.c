/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disk.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshsharma <toshsharma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 14:27:36 by toshsharma        #+#    #+#             */
/*   Updated: 2023/10/09 11:17:11 by toshsharma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

void	calculate_disk_pixel_color(t_rt *rt, t_disk disk, t_ray ray,
		double *t)
{
	t_vector	light;
	double		dot_prod;
	double		lambertian_reflection;

	light = normalize_vector(vec_subtract(rt->light->origin, vec_add(ray.origin, scalar_product(ray.direction, *t))));
	dot_prod = dot_product(disk.normal, light);
	if (dot_prod < 0)
		dot_prod = 0;
	lambertian_reflection = 1 - dot_prod;
	put_pixel(&rt->img, ray.x, ray.y, array_to_int(disk.color, lambertian_reflection));
}

void	intersect_disk(t_rt *rt, t_disk disk, t_ray ray, double *t)
{
	double		denominator;
	double		result;
	double		d_square;
	t_vector	point;

	denominator = dot_product(ray.direction, disk.normal);
	if (denominator == 0.0)
		return ;
	else
	{
		result = dot_product(vec_subtract(disk.center, ray.origin),
				disk.normal) / denominator;
		point = vec_subtract(vec_add(ray.origin,
					scalar_product(ray.direction, result)), disk.center);
		d_square = dot_product(point, point);
		if (d_square <= pow((disk.diameter / 2), 2)
			&& (result < *t && result > 0))
		{
			*t = result;
			calculate_disk_pixel_color(rt, disk, ray, t);
		}
	}
}
