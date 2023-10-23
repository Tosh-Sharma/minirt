/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshsharma <toshsharma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 16:49:25 by toshsharma        #+#    #+#             */
/*   Updated: 2023/10/23 17:21:37 by toshsharma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

int	calculate_p_color(t_rt *rt, int plane_color[3], double lam_ref)
{
	int	color;

	color = add_hex_colors(array_to_int(plane_color, 1.0),
			array_to_int(rt->ambient->color, rt->ambient->brightness));
	color = add_hex_colors(color,
			array_to_int(rt->light->color, lam_ref * rt->light->brightness));
	return (color);
}

void	calculate_plane_pixel_color(t_rt *rt, t_plane plane, t_ray ray,
		double *t)
{
	t_vector	light;
	double		t_value;

	light = normalize_vector(vec_subtract(rt->light->origin,
				vec_add(ray.origin, scalar_product(ray.direction, *t))));
	ray.normal = plane.normal;
	t_value = generate_shadow_ray(rt, ray, light, t);
	if (t_value > 0)
		put_pixel(&rt->img, ray.x, ray.y,
			calculate_p_color(rt, plane.color, 0.0));
	else
		put_pixel(&rt->img, ray.x, ray.y, calculate_p_color(rt, plane.color,
				max_num(0, dot_product(plane.normal, light))));
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
