/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshsharma <toshsharma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 16:49:12 by toshsharma        #+#    #+#             */
/*   Updated: 2023/10/26 12:33:47 by toshsharma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

double	check_for_m__in_range(t_quadratic *quad, t_cylinder cone, t_ray ray)
{
	double	m1;
	double	m2;

	m1 = (dot_product(ray.direction, cone.normal) * quad->t1)
		+ dot_product(vec_subtract(ray.origin, cone.center),
			cone.normal);
	m2 = (dot_product(ray.direction, cone.normal) * quad->t2)
		+ dot_product(vec_subtract(ray.origin, cone.center),
			cone.normal);
	if (m1 < 0 || m1 > cone.height)
		quad->t1 = INFINITY;
	if (m2 < 0 || m2 > cone.height)
		quad->t2 = INFINITY;
	return (min_num(quad->t1, quad->t2));
}

void	calculate_cone_pixel_color(t_rt *rt, t_cylinder cone, t_ray ray,
		double *t)
{
	t_vector	light;
	t_vector	normal;
	double		lambertian_reflection;

	normal = normalize_vector(vec_subtract(vec_add(ray.origin,
					scalar_product(ray.direction, *t)), cone.center));
	light = normalize_vector(vec_subtract(rt->light->origin,
				vec_add(ray.origin, scalar_product(ray.direction, *t))));
	lambertian_reflection = max_num(0, dot_product(light, normal) * -1);
	put_pixel(&rt->img, ray.x, ray.y, array_to_int(cone.color,
			lambertian_reflection));
}

void	solve_for_t_dist(t_rt *rt, t_cylinder cone, t_ray ray,
	t_quadratic *quad)
{
	double	result;

	quad->determinant = sqrt(quad->determinant);
	quad->t1 = (-(quad->b) + quad->determinant) / (2 * quad->a);
	quad->t2 = (-(quad->b) - quad->determinant) / (2 * quad->a);
	result = check_for_m__in_range(quad, cone, ray);
	if (result < *quad->t)
	{
		*quad->t = result;
		calculate_cone_pixel_color(rt, cone, ray, quad->t);
	}
}

void	intersect_cone(t_rt *rt, t_cylinder cone, t_ray ray, double *t)
{
	t_quadratic		quad;
	t_cone_solver	s;

	s.v = vectorize(ray.direction.x, ray.direction.y, ray.direction.z);
	s.w = vec_subtract(ray.origin, vec_add(cone.center,
				scalar_product(cone.normal, cone.height)));
	s.h = normalize_vector(vec_subtract(cone.center, vec_add(cone.center,
					scalar_product(cone.normal, cone.height))));
	s.m = pow((cone.diameter / 2), 2) / pow(cone.height, 2);
	quad.a = dot_product(s.v, s.v) - (s.m
			* pow(dot_product(s.v, s.h), 2)) - pow(dot_product(
				s.v, s.h), 2.0);
	quad.b = 2 * (dot_product(s.v, s.w) - (s.m
				* dot_product(s.v, s.h) * dot_product(s.w,
					s.h)) - (dot_product(s.v, s.h)
				* dot_product(s.w, s.h)));
	quad.c = dot_product(s.w, s.w) - (s.m * pow(dot_product(s.w, s.h), 2))
		- pow(dot_product(s.w, s.h), 2);
	quad.determinant = pow(quad.b, 2) - (4 * quad.a * quad.c);
	quad.t = t;
	if (quad.determinant < 0)
		return ;
	else
		solve_for_t_dist(rt, cone, ray, &quad);
}
