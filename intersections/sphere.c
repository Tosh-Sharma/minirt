/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshsharma <toshsharma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 16:49:28 by toshsharma        #+#    #+#             */
/*   Updated: 2023/10/24 23:39:11 by toshsharma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

void	calculate_inside_sphere_pixel_color(t_rt *rt, t_sphere sphere,
		t_ray ray, double *t)
{
	t_vector	light;
	t_vector	norm_light;
	double		dot_prod;
	double		lamb_f;

	light = vec_subtract(rt->light->origin,
				vec_add(ray.origin, scalar_product(ray.direction, *t)));
	norm_light = normalize_vector(light);
	ray.normal = normalize_vector(vec_subtract(sphere.center,
				vec_add(ray.origin, scalar_product(ray.direction, *t))));
	if (generate_shadow_ray(rt, ray, norm_light, t) >= 0.01)
		put_pixel(&rt->img, ray.x, ray.y, c_c(rt, sphere.color, 0.0, 0.0));
	else
	{
		dot_prod = max_num(0, dot_product(ray.normal, norm_light));
		if (vec_magnitude(vec_subtract(rt->light->origin, sphere.center))
			> sphere.diameter / 2)
			lamb_f = 1 - dot_prod;
		else
			lamb_f = dot_prod;
		put_pixel(&rt->img, ray.x, ray.y,
			c_c(rt, sphere.color, dist_ratio_rt(rt, light) * lamb_f, dist_ratio_rt(rt, light) * get_specular_factor(rt, ray.normal, ray, t)));
	}
}

void	calculate_sphere_pixel_color(t_rt *rt, t_sphere sphere, t_ray ray,
		double *t)
{
	t_vector	light;
	t_vector	norm_light;
	t_vector	normal;
	double		t_value;

	normal = normalize_vector(vec_subtract(vec_add(ray.origin,
					scalar_product(ray.direction, *t)), sphere.center));
	light = vec_subtract(rt->light->origin,
			vec_add(ray.origin, scalar_product(ray.direction, *t)));
	norm_light = normalize_vector(light);
	ray.normal = normal;
	t_value = generate_shadow_ray(rt, ray, norm_light, t);
	if (t_value >= 0.01)
		put_pixel(&rt->img, ray.x, ray.y,
			c_c(rt, sphere.color, 0.0, 0.0));
	else
	{
		// rt->camera.view = dist_ratio_rt(rt, light) * (max_num(0, dot_product(normal, norm_light)) + get_specular_factor(rt, normal, ray, t));
		put_pixel(&rt->img, ray.x, ray.y, c_c(rt, sphere.color,
				dist_ratio_rt(rt, light) * max_num(0, dot_product(normal,
				norm_light)),  dist_ratio_rt(rt, light) *
				get_specular_factor(rt, normal, ray, t)));
	}
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
	t_quadratic	quad;

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
