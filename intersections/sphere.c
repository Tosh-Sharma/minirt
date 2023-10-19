/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshsharma <toshsharma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 16:49:28 by toshsharma        #+#    #+#             */
/*   Updated: 2023/10/19 15:26:21 by toshsharma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

int	calculate_s_color(t_rt *rt, int sphere_color[3], double lam_ref)
{
	int	color;

	color = add_hex_colors(array_to_int(sphere_color, rt->ambient->brightness),
			array_to_int(rt->ambient->color, rt->ambient->brightness));
	color = add_hex_colors(color,
			array_to_int(rt->light->color, lam_ref * rt->light->brightness));
	return (color);
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
	if (t_value > 0)
		put_pixel(&rt->img, ray.x, ray.y,
			calculate_s_color(rt, sphere.color, 0.0));
	else
		put_pixel(&rt->img, ray.x, ray.y, calculate_s_color(rt, sphere.color,
				max_num(0, dot_product(normal, light))));
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
		- pow(sphere.diameter / 2, 2.0);
	discriminant = pow(b, 2.0) - (4.0 * a * c);
	if (discriminant < 0.0)
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
