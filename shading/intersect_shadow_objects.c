/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_shadow_objects.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshsharma <toshsharma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 16:01:52 by toshsharma        #+#    #+#             */
/*   Updated: 2023/10/23 16:19:27 by toshsharma       ###   ########.fr       */
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
		return (solve_shadow_for_t(cylinder, ray, &quad));
}
