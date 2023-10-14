/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshsharma <toshsharma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 16:49:25 by toshsharma        #+#    #+#             */
/*   Updated: 2023/09/09 23:47:04 by toshsharma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

void	calculate_plane_pixel_color(t_rt *rt, t_plane plane, t_ray ray,
		double *t)
{
	t_vector	light;
	double		dot_prod;
	double		lambertian_reflection;
	double		t_value;

	light = normalize_vector(vec_subtract(rt->light->origin, vec_add(ray.origin, scalar_product(ray.direction, *t))));
	ray.normal = plane.normal;
	t_value = generate_shadow_ray(rt, ray, light, t);
	if (t_value > 0)
		put_pixel(&rt->img, ray.x, ray.y, t_value * 0);
	else
	{
		dot_prod = dot_product(plane.normal, light);
		if (dot_prod < 0)
			dot_prod = 0;
		lambertian_reflection = dot_prod;
		put_pixel(&rt->img, ray.x, ray.y, array_to_int(plane.color, lambertian_reflection));
	}
}

void	intersect_plane(t_rt *rt, t_plane plane, t_ray ray, double *t)
{
	double	denominator;
	double	result;

	denominator = dot_product(ray.direction, plane.normal);
	if (denominator == 0)
		return ;
	else
	{
		result = dot_product(vec_subtract(plane.center, ray.origin),
				plane.normal) / denominator;
		if (result < 0)
			return ;
		else if (result < *t && result > 0)
		{
			*t = result;
			calculate_plane_pixel_color(rt, plane, ray, t);
		}
	}
}
