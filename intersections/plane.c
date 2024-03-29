/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshsharma <toshsharma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 16:49:25 by toshsharma        #+#    #+#             */
/*   Updated: 2023/10/26 16:22:50 by toshsharma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

void	calculate_plane_pixel_color(t_rt *rt, t_plane plane, t_ray ray,
		double *t)
{
	t_vector	light;
	t_vector	norm_light;
	double		t_value;

	light = vec_subtract(rt->light->origin,
			vec_add(ray.origin, scalar_product(ray.direction, *t)));
	norm_light = normalize_vector(light);
	ray.normal = plane.normal;
	t_value = generate_shadow_ray(rt, ray, norm_light, t);
	if (t_value >= 0.01)
		put_pixel(&rt->img, ray.x, ray.y,
			c_c(rt, plane.color, 0.0, 0.0));
	else
	{
		put_pixel(&rt->img, ray.x, ray.y, c_c(rt, plane.color,
				dist(rt, light) * max_num(0,
					dot(plane.normal, norm_light)),
				dist(rt, light) * spec(rt, plane.normal, ray, t)));
	}
}

void	intersect_plane(t_rt *rt, t_plane plane, t_ray ray, double *t)
{
	double	denominator;
	double	result;

	denominator = dot(ray.direction, plane.normal);
	if (denominator == 0)
		return ;
	else
	{
		result = dot(vec_subtract(plane.center, ray.origin),
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
