/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshsharma <toshsharma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 16:49:28 by toshsharma        #+#    #+#             */
/*   Updated: 2023/10/15 15:25:49 by toshsharma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

int	calculate_color(t_rt *rt, t_vector v1, t_vector v2, int *color)
{
	double	lamb_refl;
	int		result_color;

	lamb_refl = max_num(0, dot_product(v1, v2));
	(void)rt;
	result_color = array_to_int(color, lamb_refl);
	return (result_color);
}

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
	// double		lamb_refl;

	normal = normalize_vector(vec_subtract(vec_add(ray.origin,
					scalar_product(ray.direction, *t)), sphere.center));
	light = normalize_vector(vec_subtract(rt->light->origin,
				vec_add(ray.origin, scalar_product(ray.direction, *t))));
	// lamb_refl = max_num(0, dot_product(light, normal));
	// put_pixel(&rt->img, ray.x, ray.y, add_two_colors(sphere.color, lamb_refl,
	// 		rt->ambient->color, rt->ambient->brightness));
	put_pixel(&rt->img, ray.x, ray.y, calculate_color(rt, normal, light,
			sphere.color));
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
