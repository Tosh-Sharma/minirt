/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshsharma <toshsharma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 16:19:20 by toshsharma        #+#    #+#             */
/*   Updated: 2023/10/26 16:22:50 by toshsharma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

double	spec(t_rt *rt, t_vector normal, t_ray ray, double *t)
{
	t_vector	cam;
	t_vector	incident_ray;
	t_vector	calcul;
	double		dot_prod;
	double		result;

	incident_ray = normalize_vector(vec_subtract(vec_add(ray.origin,
					scalar_product(ray.direction, *t)), rt->light->origin));
	dot_prod = dot(normal, incident_ray);
	calcul = scalar_product(normal, 2.0 * dot_prod);
	calcul = vec_subtract(calcul, incident_ray);
	cam = normalize_vector(vec_subtract(rt->camera.origin,
				vec_add(ray.origin, scalar_product(ray.direction, *t))));
	result = max_num(0.0, dot(calcul, scalar_product(cam, -1.0)));
	result = pow(result, 64);
	return (result);
}

double	dist(t_rt *rt, t_vector light)
{
	double	distance;
	double	factor;

	factor = 500 * rt->light->brightness;
	distance = vec_magnitude(light);
	if (distance < 0)
		distance *= -1;
	if (distance > (factor))
		return (0.0);
	else
		return (1 - (distance / factor));
}
