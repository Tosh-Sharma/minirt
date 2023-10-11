/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow_ray.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshsharma <toshsharma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 16:04:58 by tsharma           #+#    #+#             */
/*   Updated: 2023/09/03 17:26:57 by toshsharma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

double	intersect_shadow_plane(t_plane plane, t_ray ray, double *t)
{
	double	denominator;
	double	result;

	denominator = dot_product(ray.direction, plane.normal);
	if (denominator == 0)
		return (0.0);
	else
	{
		result = dot_product(vec_subtract(plane.center, ray.origin),
				plane.normal) / denominator;
		if (result < 0)
			return (0.0);
		else if (result < *t && result > 0)
			return (result);
        else
            return (0.0);
	}
}

double	intersect_shadow_sphere(t_sphere sphere, t_ray ray, double *t)
{
	double	a;
	double	b;
	double	c;
	double	discriminant;
	double	new_t;

	a = 1;
	b = 2 * dot_product(ray.direction, vec_subtract(ray.origin,
				sphere.center));
	c = dot_product(vec_subtract(ray.origin, sphere.center),
			vec_subtract(ray.origin, sphere.center))
		- (powf(sphere.diameter / 2, 2));
	discriminant = (b * b) - (4 * a * c);
	if (discriminant < 0)
		return (0.0);
	else
	{
		new_t = min_num((-b + sqrt(discriminant)) / (2 * a),
				(-b - sqrt(discriminant)) / (2 * a));				
		if (new_t > 0 && new_t < *t)
            return (new_t);
        else
            return (0.0);
	}
}

double	iterate_shadow_over_objects(t_rt *rt, t_ray ray, double *t)
{
	t_uint	i;
    double  t_value;

	i = -1;
    t_value = 0.0;
	while (++i < rt->max_sp)
    {
        t_value = intersect_shadow_sphere(rt->sphere[i], ray, t);
        if (t_value > 0.0)
            return (t_value);
    }
	i = -1;
	while (++i < rt->max_pl)
    {
        t_value = intersect_shadow_plane(rt->plane[i], ray, t);
        if (t_value > 0.0)
            return (t_value);
    }
	i = -1;
	while (++i < rt->max_cy)
    {
        t_value = intersect_shadow_cylinder(rt->cylinder[i], ray, t);
        if (t_value > 0.0)
            return (t_value);
    }
    return (0.0);
}

double	generate_shadow_ray(t_rt *rt, t_ray ray, t_vector light, double *t)
{
	t_ray	shadow_ray;
    double  t_value;
    double  new_t;

	shadow_ray.origin = vec_add(vec_add(ray.origin, scalar_product(ray.direction, *t)), scalar_product(ray.normal, 0.01));
	shadow_ray.direction = vectorize(light.x, light.y, light.z);
	shadow_ray.x = ray.x;
	shadow_ray.y = ray.y;
    new_t = INFINITY;
    shadow_ray.flag = 1;
    t_value = iterate_shadow_over_objects(rt, shadow_ray, &new_t);
	return (t_value);
}
