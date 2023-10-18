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

double	solve_shadow_for_t(t_cylinder cylinder, t_ray ray, t_quadratic *quad)
{
	double	result;

	quad->determinant = sqrt(quad->determinant);
	quad->t1 = (-(quad->b) + quad->determinant) / (2 * quad->a);
	quad->t2 = (-(quad->b) - quad->determinant) / (2 * quad->a);
	result = check_for_m_in_range(quad, cylinder, ray);
	if (result < *quad->t)
		return (result);
	return (0.0);
}

double	intersect_shadow_disk(t_disk disk, t_ray ray, double *t)
{
	double		denominator;
	double		result;
	double		d_square;
	t_vector	point;

	denominator = dot_product(ray.direction, disk.normal);
	if (denominator == 0)
		return (0.0);
	else
	{
		result = dot_product(vec_subtract(disk.center, ray.origin),
				disk.normal) / denominator;
		point = vec_subtract(vec_add(ray.origin,
					scalar_product(ray.direction, result)), disk.center);
		d_square = dot_product(point, point);
		if (d_square <= pow((disk.diameter / 2), 2)
			&& (result < *t && result > 0))
			return (result);
		else
			return (0.0);
	}
}

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

double	intersect_shadow_cylinder(t_cylinder cylinder, t_ray ray, double *t)
{
	t_quadratic	quad;
	double		disk_t_value;

	disk_t_value = handle_shadow_disks(cylinder, ray, t);
	if (disk_t_value > 0.0)
		return (disk_t_value);
	quad.a = dot_product(ray.direction, ray.direction)
		- pow(dot_product(ray.direction, cylinder.normal), 2);
	quad.b = 2 * (dot_product(ray.direction, vec_subtract(ray.origin,
					cylinder.center))
			- (dot_product(ray.direction, cylinder.normal)
				* dot_product(vec_subtract(ray.origin, cylinder.center),
					cylinder.normal)));
	quad.c = dot_product(vec_subtract(ray.origin, cylinder.center),
			vec_subtract(ray.origin, cylinder.center))
		- pow(dot_product(vec_subtract(ray.origin, cylinder.center),
				cylinder.normal), 2)
		- pow(cylinder.diameter / 2, 2);
	quad.determinant = pow(quad.b, 2) - (4 * quad.a * quad.c);
	quad.t = t;
	if (quad.determinant < 0.0)
		return (0.0);
	else
		return(solve_shadow_for_t(cylinder, ray, &quad));
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
	new_t = vec_magnitude(vec_subtract(shadow_ray.origin, rt->light->origin));
    t_value = iterate_shadow_over_objects(rt, shadow_ray, &new_t);
    // printf("t_v G_S_R = %f/n", t_value);
	return (t_value);
}
