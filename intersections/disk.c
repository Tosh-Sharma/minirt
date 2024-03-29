/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disk.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshsharma <toshsharma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 14:27:36 by toshsharma        #+#    #+#             */
/*   Updated: 2023/10/26 16:23:19 by toshsharma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

void	calculate_disk_pixel_color(t_rt *rt, t_disk disk, t_ray ray,
		double *t)
{
	t_vector	light;
	t_vector	norm_light;
	double		t_value;

	light = vec_subtract(rt->light->origin, vec_add(ray.origin,
				scalar_product(ray.direction, *t)));
	norm_light = normalize_vector(light);
	ray.normal = disk.normal;
	if (!rt->light_inside && rt->cam_inside)
		t_value = 0;
	else
		t_value = generate_shadow_ray(rt, ray, norm_light, t);
	if (t_value >= 0.01)
		put_pixel(&rt->img, ray.x, ray.y,
			c_c(rt, disk.color, 0.0, 0.0));
	else
	{
		if (rt->cam_inside && rt->light_inside)
			put_pixel(&rt->img, ray.x, ray.y, c_c(rt, disk.color,
					(1 / (vec_magnitude(light))), 0.0));
		else
			put_pixel(&rt->img, ray.x, ray.y, c_c(rt, disk.color, dist(rt,
						light) * max_num(0.0, dot(ray.normal, norm_light)),
					dist(rt, light) * spec(rt, ray.normal, ray, t)));
	}	
}

void	intersect_disk(t_rt *rt, t_disk disk, t_ray ray, double *t)
{
	double		denominator;
	double		result;
	double		d_square;
	t_vector	point;

	denominator = dot(ray.direction, disk.normal);
	if (denominator == 0.0)
		return ;
	else
	{
		result = dot(vec_subtract(disk.center, ray.origin),
				disk.normal) / denominator;
		point = vec_subtract(vec_add(ray.origin,
					scalar_product(ray.direction, result)), disk.center);
		d_square = dot(point, point);
		if (d_square <= pow((disk.diameter / 2), 2)
			&& (result < *t && result > 0))
		{
			*t = result;
			calculate_disk_pixel_color(rt, disk, ray, t);
		}
	}
}

void	handle_disks(t_rt *rt, t_cylinder cylinder, t_ray ray, double *t)
{
	t_disk		top_disk;
	t_disk		bottom_disk;

	rt->cam_inside = cam_inside_or_not(rt, cylinder);
	bottom_disk.center = scalar_product(cylinder.center, 1);
	if (rt->cam_inside == 1)
	{
		bottom_disk.normal = scalar_product(cylinder.normal, 1);
		top_disk.normal = scalar_product(cylinder.normal, -1);
	}
	else
	{
		bottom_disk.normal = scalar_product(cylinder.normal, -1);
		top_disk.normal = scalar_product(cylinder.normal, 1);
	}
	top_disk.center = vec_add(cylinder.center,
			scalar_product(cylinder.normal, cylinder.height));
	top_disk.diameter = cylinder.diameter;
	bottom_disk.diameter = cylinder.diameter;
	copy_colors(cylinder.color, top_disk.color);
	copy_colors(cylinder.color, bottom_disk.color);
	intersect_disk(rt, top_disk, ray, t);
	intersect_disk(rt, bottom_disk, ray, t);
}
