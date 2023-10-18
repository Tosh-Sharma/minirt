/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshsharma <toshsharma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 16:49:28 by toshsharma        #+#    #+#             */
/*   Updated: 2023/10/16 11:48:17 by toshsharma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

// Calculating lambertian reflection.
// LambertianReflection = max⁡(0, N.L)
// N is the normal vector of the surface at the point of intersection.
// L is the vector pointing from the point of intersection to the light source.
// DiffuseContribution = LambertianReflection × lightcolor × lightbrightness

void	calculate_inside_sphere_pixel_color(t_rt *rt, t_sphere sphere, t_ray ray,
		double *t)
{
	t_vector	light;
	t_vector	normal;
	double		dot_prod;
	double		lambertian_reflection;
	double		t_value;

	normal = normalize_vector(vec_subtract(sphere.center, vec_add(ray.origin, //besoin d'inverser le sens (comprndre avec geogebra)
		scalar_product(ray.direction, *t))));
	light = normalize_vector(vec_subtract(rt->light->origin,
		vec_add(ray.origin, scalar_product(ray.direction, *t))));
	ray.normal = normal;
	t_value = generate_shadow_ray(rt, ray, light, t);
	if (t_value > 0.0) 
		put_pixel(&rt->img, ray.x, ray.y, 0);
	else
	{
		dot_prod = dot_product(normal, light);
		if (dot_prod < 0.0)
			dot_prod = 0;
		if (vec_magnitude(vec_subtract(rt->light->origin, sphere.center)) > sphere.diameter / 2)
			lambertian_reflection = 1 - dot_prod;
		else
			lambertian_reflection = dot_prod;
		put_pixel(&rt->img, ray.x, ray.y, array_to_int(sphere.color,
			lambertian_reflection));
	}
}

void	calculate_sphere_pixel_color(t_rt *rt, t_sphere sphere, t_ray ray,
		double *t)
{
	t_vector	light;
	t_vector	normal;
	double		dot_prod;
	double		lambertian_reflection;
	double		t_value;

	normal = normalize_vector(vec_subtract(vec_add(ray.origin,
				scalar_product(ray.direction, *t)), sphere.center));
	light = normalize_vector(vec_subtract(rt->light->origin,
			vec_add(ray.origin, scalar_product(ray.direction, *t))));
	ray.normal = normal;
	t_value = generate_shadow_ray(rt, ray, light, t);
	if (t_value > 0.0) 
		put_pixel(&rt->img, ray.x, ray.y, 0);
	else
	{
		dot_prod = dot_product(normal, light);
		if (dot_prod < 0.0)
			dot_prod = 0;
		lambertian_reflection = dot_prod;
		put_pixel(&rt->img, ray.x, ray.y, array_to_int(sphere.color,
				lambertian_reflection));
	}
}

void	intersect_sphere(t_rt *rt, t_sphere sphere, t_ray ray, double *t)
{
	double		a;
	double		b;
	double		c;
	double		discriminant;
	double		new_t;
	t_vector	dist;

	a = 1;
	b = 2 * dot_product(ray.direction, vec_subtract(ray.origin,
				sphere.center));
	c = dot_product(vec_subtract(ray.origin, sphere.center),
			vec_subtract(ray.origin, sphere.center))
		- pow(sphere.diameter / 2, 2.0);
	discriminant = pow(b, 2.0) - (4.0 * a * c);
	if (discriminant < 0.0)
		return ;
	else
	{
		new_t = min_num((-b + sqrt(discriminant)) / (2 * a),
				(-b - sqrt(discriminant)) / (2 * a));
		dist = vec_subtract(rt->camera.origin, sphere.center);
		if (dot_product(dist, dist) < (sphere.diameter / 2) * (sphere.diameter / 2) && (-new_t < *t))
		{
			*t = new_t * (-1);
			calculate_inside_sphere_pixel_color(rt, sphere, ray, t);
		}
		else if (new_t > 0 && new_t < *t)
		{
			*t = new_t;
			calculate_sphere_pixel_color(rt, sphere, ray, t);
		}
	}
}
