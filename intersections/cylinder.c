/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshsharma <toshsharma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 16:49:22 by toshsharma        #+#    #+#             */
/*   Updated: 2023/10/26 16:25:56 by toshsharma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

void	print_inside_tube(t_rt *rt, t_vector *vector, t_ray ray,
		t_cylinder cylinder)
{
	double		lambertian_reflection;
	double		dot_prod;

	dot_prod = dot(vector[0], vector[2]);
	if (dot_prod < 0.0)
		dot_prod = 0;
	rt->light_inside = light_inside_or_not(rt, cylinder);
	if (rt->light_inside)
		put_pixel(&rt->img, ray.x, ray.y, c_c(rt, cylinder.color,
				dist(rt, vector[1]) * dot_prod, 0.0));
	else
	{
		lambertian_reflection = 1 - dot_prod;
		put_pixel(&rt->img, ray.x, ray.y, c_c(rt, cylinder.color,
				dist(rt, vector[1]) * lambertian_reflection, 0.0));
	}
}

void	calculate_inside_tube_pixel_color(t_rt *rt, t_cylinder cylinder,
		t_ray ray, double *t)
{
	t_vector	light;
	t_vector	norm_light;
	t_vector	normal;
	double		t_value;
	double		calcul;

	calcul = dot(vec_subtract(vec_add(ray.origin, scalar_product(
						ray.direction, *t)), cylinder.center), cylinder.normal);
	normal = vec_add(cylinder.center, scalar_product(cylinder.normal, calcul));
	normal = normalize_vector(vec_subtract(normal, vec_add(ray.origin,
					scalar_product(ray.direction, *t))));
	light = vec_subtract(rt->light->origin,
			vec_add(ray.origin, scalar_product(ray.direction, *t)));
	norm_light = normalize_vector(vec_subtract(rt->light->origin,
				vec_add(ray.origin, scalar_product(ray.direction, *t))));
	t_value = generate_shadow_ray(rt, ray, norm_light, t);
	if (t_value >= 0.01)
		put_pixel(&rt->img, ray.x, ray.y,
			c_c(rt, cylinder.color, 0.0, 0.0));
	else
		print_inside_tube(rt, (t_vector[3]){normal, light, norm_light},
			ray, cylinder);
}

void	calculate_tube_pixel_color(t_rt *rt, t_cylinder cylinder, t_ray ray,
		double *t)
{
	t_vector	light;
	t_vector	norm_light;
	t_vector	normal;
	double		t_value;
	double		calcul;

	calcul = dot(vec_subtract(vec_add(ray.origin, scalar_product(
						ray.direction, *t)), cylinder.center), cylinder.normal);
	normal = vec_add(cylinder.center, scalar_product(cylinder.normal, calcul));
	normal = normalize_vector(vec_subtract(vec_add(ray.origin, scalar_product(
						ray.direction, *t)), normal));
	light = vec_subtract(rt->light->origin,
			vec_add(ray.origin, scalar_product(ray.direction, *t)));
	norm_light = normalize_vector(light);
	t_value = generate_shadow_ray(rt, ray, norm_light, t);
	if (t_value >= 0.01)
		put_pixel(&rt->img, ray.x, ray.y,
			c_c(rt, cylinder.color, 0.0, 0.0));
	else
	{
		put_pixel(&rt->img, ray.x, ray.y, c_c(rt, cylinder.color,
				dist(rt, light) * (max_num(0, dot(normal, norm_light))),
				dist(rt, light) * spec(rt, normal, ray, t)));
	}
}

// The following equations are written with assuming that the cylinder center
// is placed at base of the cylinder instead of the center 
// point of the central axis.
void	intersect_cylinder(t_rt *rt, t_cylinder cylinder, t_ray ray, double *t)
{
	t_quadratic	quad;

	handle_disks(rt, cylinder, ray, t);
	quad.a = dot(ray.direction, ray.direction)
		- pow(dot(ray.direction, cylinder.normal), 2);
	quad.b = 2 * (dot(ray.direction, vec_subtract(ray.origin,
					cylinder.center))
			- (dot(ray.direction, cylinder.normal)
				* dot(vec_subtract(ray.origin, cylinder.center),
					cylinder.normal)));
	quad.c = dot(vec_subtract(ray.origin, cylinder.center),
			vec_subtract(ray.origin, cylinder.center))
		- pow(dot(vec_subtract(ray.origin, cylinder.center),
				cylinder.normal), 2)
		- pow(cylinder.diameter / 2, 2);
	quad.determinant = pow(quad.b, 2) - (4 * quad.a * quad.c);
	quad.t = t;
	if (quad.determinant < 0)
		return ;
	else
		solve_for_t(rt, cylinder, ray, &quad);
}
