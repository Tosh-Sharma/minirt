/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow_ray.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshsharma <toshsharma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 16:03:36 by toshsharma        #+#    #+#             */
/*   Updated: 2023/10/23 16:05:26 by toshsharma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

double	handle_shadow_disks(t_cylinder cylinder, t_ray ray, double *t)
{
	t_disk		top_disk;
	t_disk		bottom_disk;
	double		t_value;

	bottom_disk.center = scalar_product(cylinder.center, 1);
	bottom_disk.normal = scalar_product(cylinder.normal, -1);
	top_disk.normal = scalar_product(cylinder.normal, 1);
	top_disk.center = vec_add(cylinder.center,
			scalar_product(cylinder.normal, cylinder.height));
	top_disk.diameter = cylinder.diameter;
	bottom_disk.diameter = cylinder.diameter;
	copy_colors(cylinder.color, top_disk.color);
	copy_colors(cylinder.color, bottom_disk.color);
	t_value = intersect_shadow_disk(top_disk, ray, t);
	if (t_value > 0.0)
		return (t_value);
	t_value = intersect_shadow_disk(bottom_disk, ray, t);
	if (t_value > 0.0)
		return (t_value);
	return (0.0);
}

double	iterate_shadow_over_objects(t_rt *rt, t_ray ray, double *t)
{
	t_uint	i;
	double	t_value;

	i = -1;
	t_value = 0.0;
	while (++i < rt->max_sp)
	{
		t_value = intersect_shadow_sphere(rt->sphere[i], ray, t);
		if (t_value > 0.01)
			return (t_value);
	}
	i = -1;
	while (++i < rt->max_pl)
	{
		t_value = intersect_shadow_plane(rt->plane[i], ray, t);
		if (t_value > 0.01)
			return (t_value);
	}
	i = -1;
	while (++i < rt->max_cy)
	{
		t_value = intersect_shadow_cylinder(rt->cylinder[i], ray, t);
		if (t_value > 0.01)
			return (t_value);
	}
	return (0.0);
}

double	generate_shadow_ray(t_rt *rt, t_ray ray, t_vector light, double *t)
{
	t_ray	shadow_ray;
	double	t_value;
	double	new_t;

	shadow_ray.origin = vec_add(vec_add(ray.origin, scalar_product(
					ray.direction, *t)), scalar_product(ray.normal, 0.01));
	shadow_ray.direction = vectorize(light.x, light.y, light.z);
	shadow_ray.x = ray.x;
	shadow_ray.y = ray.y;
	new_t = vec_magnitude(vec_subtract(shadow_ray.origin, rt->light->origin));
	t_value = iterate_shadow_over_objects(rt, shadow_ray, &new_t);
	return (t_value);
}
