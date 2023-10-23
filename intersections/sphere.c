/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshsharma <toshsharma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 16:49:28 by toshsharma        #+#    #+#             */
/*   Updated: 2023/10/23 16:21:55 by toshsharma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

// Calculating lambertian reflection.
// LambertianReflection = max⁡(0, N.L)
// N is the normal vector of the surface at the point of intersection.
// L is the vector pointing from the point of intersection to the light source.
// DiffuseContribution = LambertianReflection × lightcolor × lightbrightness

void	calculate_inside_sphere_pixel_color(t_rt *rt, t_sphere sphere,
		t_ray ray, double *t)
{
	t_vector	light;
	t_vector	normal;
	double		dot_prod;
	double		lamb_f;
	double		t_value;

	normal = normalize_vector(vec_subtract(sphere.center, vec_add(ray.origin,
					scalar_product(ray.direction, *t))));
	light = normalize_vector(vec_subtract(rt->light->origin,
				vec_add(ray.origin, scalar_product(ray.direction, *t))));
	ray.normal = normal;
	t_value = generate_shadow_ray(rt, ray, light, t);
	if (t_value >= 0.01)
		put_pixel(&rt->img, ray.x, ray.y,
			calculate_color(rt, sphere.color, 0.0));
	else
	{
		dot_prod = max_num(0, dot_product(normal, light));
		if (vec_magnitude(vec_subtract(rt->light->origin, sphere.center))
			> sphere.diameter / 2)
			lamb_f = 1 - dot_prod;
		else
			lamb_f = dot_prod;
		put_pixel(&rt->img, ray.x, ray.y,
				calculate_color(rt, sphere.color, lamb_f));
	}
}

void	calculate_sphere_pixel_color(t_rt *rt, t_sphere sphere, t_ray ray,
		double *t)
{
	t_vector	light;
	t_vector	normal;
	double		t_value;

	normal = normalize_vector(vec_subtract(vec_add(ray.origin,
					scalar_product(ray.direction, *t)), sphere.center));
	light = normalize_vector(vec_subtract(rt->light->origin,
				vec_add(ray.origin, scalar_product(ray.direction, *t))));
	ray.normal = normal;
	t_value = generate_shadow_ray(rt, ray, light, t);
	if (t_value >= 0.01)
		put_pixel(&rt->img, ray.x, ray.y,
			calculate_color(rt, sphere.color, 0.0));
	else
		put_pixel(&rt->img, ray.x, ray.y, calculate_color(rt, sphere.color,
				max_num(0, dot_product(normal, light))));
}

void	intersect_sphere_else(t_rt *rt, t_sphere sphere, t_ray ray,
	t_quadratic *quad)
{
	t_vector	dist;
	double		new_t;

	new_t = min_num((-(quad->b) + sqrt(quad->determinant)) / (2 * quad->a),
			(-(quad->b) - sqrt(quad->determinant)) / (2 * quad->a));
	dist = vec_subtract(rt->camera.origin, sphere.center);
	if (dot_product(dist, dist) < (sphere.diameter / 2)
		* (sphere.diameter / 2) && (-new_t < *quad->t))
	{
		*quad->t = new_t * (-1);
		calculate_inside_sphere_pixel_color(rt, sphere, ray, quad->t);
	}
	else if (new_t > 0 && new_t < *quad->t)
	{
		*quad->t = new_t;
		calculate_sphere_pixel_color(rt, sphere, ray, quad->t);
	}
}

void	intersect_sphere(t_rt *rt, t_sphere sphere, t_ray ray, double *t)
{
	t_quadratic quad;

	quad.a = 1;
	quad.b = 2 * dot_product(ray.direction, vec_subtract(ray.origin,
				sphere.center));
	quad.c = dot_product(vec_subtract(ray.origin, sphere.center),
			vec_subtract(ray.origin, sphere.center))
		- pow(sphere.diameter / 2, 2.0);
	quad.determinant = pow(quad.b, 2.0) - (4.0 * quad.a * quad.c);
	quad.t = t;
	if (quad.determinant < 0.0)
		return ;
	else
		intersect_sphere_else(rt, sphere, ray, &quad);
}
