/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshsharma <toshsharma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 16:49:28 by toshsharma        #+#    #+#             */
/*   Updated: 2023/09/12 21:24:53 by toshsharma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

// Calculating lambertian reflection.
// LambertianReflection = max⁡(0, N.L)
// N is the normal vector of the surface at the point of intersection.
// L is the vector pointing from the point of intersection to the light source.
// DiffuseContribution = LambertianReflection × lightcolor × lightbrightness

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
	if (t_value > 0)
		put_pixel(&rt->img, ray.x, ray.y, 0);
	else
	{
		dot_prod = dot_product(normal, light);
		if (dot_prod < 0)
			dot_prod = 0;
		lambertian_reflection = dot_prod;
		put_pixel(&rt->img, ray.x, ray.y, array_to_int(sphere.color,
			lambertian_reflection));
	}
}

void	intersect_sphere(t_rt *rt, t_sphere sphere, t_ray ray, double *t)
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
		return ;
	else
	{
		new_t = min_num((-b + sqrt(discriminant)) / (2 * a),
				(-b - sqrt(discriminant)) / (2 * a));				
		if (new_t > 0 && new_t < *t)
		{
			*t = new_t;
			calculate_sphere_pixel_color(rt, sphere, ray, t);
		}
	}
}
