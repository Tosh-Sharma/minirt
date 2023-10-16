/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshsharma <toshsharma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 16:49:22 by toshsharma        #+#    #+#             */
/*   Updated: 2023/10/09 14:43:41 by toshsharma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

void	handle_disks(t_rt *rt, t_cylinder cylinder, t_ray ray, double *t)
{
	t_disk		top_disk;
	t_disk		bottom_disk;

	bottom_disk.center = scalar_product(cylinder.center, 1);
	bottom_disk.normal = scalar_product(cylinder.normal, -1);
	top_disk.normal = scalar_product(cylinder.normal, 1);
	top_disk.center = vec_add(cylinder.center,
			scalar_product(cylinder.normal, cylinder.height));
	top_disk.diameter = cylinder.diameter;
	bottom_disk.diameter = cylinder.diameter;
	copy_colors(cylinder.color, top_disk.color);
	copy_colors(cylinder.color, bottom_disk.color);
	intersect_disk(rt, top_disk, ray, t);
	intersect_disk(rt, bottom_disk, ray, t);
}

double	check_for_m_in_range(t_quadratic *quad, t_cylinder cylinder, t_ray ray)
{
	double	m1;
	double	m2;

	m1 = (dot_product(ray.direction, cylinder.normal) * quad->t1)
		+ dot_product(vec_subtract(ray.origin, cylinder.center),
			cylinder.normal);
	m2 = (dot_product(ray.direction, cylinder.normal) * quad->t2)
		+ dot_product(vec_subtract(ray.origin, cylinder.center),
			cylinder.normal);
	if (m1 < 0 || m1 > cylinder.height)
		quad->t1 = INFINITY;
	if (m2 < 0 || m2 > cylinder.height)
		quad->t2 = INFINITY;
	return (min_num(quad->t1, quad->t2));
}

void	calculate_tube_pixel_color(t_rt *rt, t_cylinder cylinder, t_ray ray,
		double *t)
{
	t_vector	light;
	t_vector	normal;
	double		t_value;
	double		calcul;
	double		lambertian_reflection;
	double		dot_prod;

	calcul = dot_product(vec_subtract(vec_add(ray.origin, scalar_product(ray.direction, *t)), cylinder.center), cylinder.normal);
	normal = vec_add(cylinder.center, scalar_product(cylinder.normal, calcul));
	normal = normalize_vector(vec_subtract(vec_add(ray.origin, scalar_product(ray.direction, *t)), normal));
	light = normalize_vector(vec_subtract(rt->light->origin,
				vec_add(ray.origin, scalar_product(ray.direction, *t))));
	t_value = generate_shadow_ray(rt, ray, light, t);
	if (t_value > 0.01)
		put_pixel(&rt->img, ray.x, ray.y, 0);
	else
	{
		dot_prod = dot_product(normal, light);
		if (dot_prod < 0.0)
			dot_prod = 0;
		lambertian_reflection = dot_prod;
		put_pixel(&rt->img, ray.x, ray.y, array_to_int(cylinder.color,
			lambertian_reflection));
	}
}

void	solve_for_t(t_rt *rt, t_cylinder cylinder, t_ray ray, t_quadratic *quad)
{
	double	result;

	quad->determinant = sqrt(quad->determinant);
	quad->t1 = (-(quad->b) + quad->determinant) / (2 * quad->a);
	quad->t2 = (-(quad->b) - quad->determinant) / (2 * quad->a);
	result = check_for_m_in_range(quad, cylinder, ray);
	if (result < *quad->t)
	{
		*quad->t = result;
		calculate_tube_pixel_color(rt, cylinder, ray, quad->t);
	}
}

// The following equations are written with assuming that the cylinder center
// is placed at base of the cylinder instead of the center 
// point of the central axis.
void	intersect_cylinder(t_rt *rt, t_cylinder cylinder, t_ray ray, double *t)
{
	t_quadratic	quad;

	handle_disks(rt, cylinder, ray, t);
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
	if (quad.determinant < 0)
		return ;
	else
		solve_for_t(rt, cylinder, ray, &quad);
}
