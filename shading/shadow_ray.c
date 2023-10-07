/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow_ray.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshsharma <toshsharma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 16:04:58 by tsharma           #+#    #+#             */
/*   Updated: 2023/09/03 17:26:57 by toshsharma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

double  vector_distance(t_vector light, t_ray ray, double *t)
{
    t_vector    v_ray;

    v_ray = vec_subtract(scalar_product(ray.direction, *t), ray.origin);
    printf("%f\n",vec_magnitude(v_ray) - vec_magnitude(light));
    return (vec_magnitude(v_ray) - vec_magnitude(light));
}

void	generate_shadow_ray(t_rt *rt, t_ray ray, t_vector light, double *t)
{
	t_ray	shadow_ray;

	shadow_ray.origin = vec_add(ray.origin, scalar_product(ray.direction, *t));
	shadow_ray.direction = vectorize(light.x, light.y, light.z);
	shadow_ray.x = ray.x;
	shadow_ray.y = ray.y;
    shadow_ray.flag = 1;
	iterate_over_objects(rt, shadow_ray, t);
}