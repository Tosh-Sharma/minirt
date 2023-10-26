/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshsharma <toshsharma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 16:07:02 by toshsharma        #+#    #+#             */
/*   Updated: 2023/10/26 16:22:36 by toshsharma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

int	light_inside_or_not(t_rt *rt, t_cylinder cylinder)
{
	double		calcul;
	t_vector	normal;
	double		dist_cam;

	calcul = dot(vec_subtract(rt->light[0].origin, cylinder.center),
			cylinder.normal);
	if (calcul < 0)
		return (0);
	normal = vec_add(cylinder.center, scalar_product(cylinder.normal, calcul));
	normal = vec_subtract(rt->light[0].origin, normal);
	dist_cam = vec_magnitude(normal);
	if (dist_cam < cylinder.diameter / 2)
		return (1);
	else
		return (0);
}

int	cam_inside_or_not(t_rt *rt, t_cylinder cylinder)
{
	double		calcul;
	t_vector	normal;
	double		dist_cam;

	calcul = dot(vec_subtract(rt->camera.origin, cylinder.center),
			cylinder.normal);
	if (calcul < 0 || calcul > cylinder.height)
		return (0);
	normal = vec_add(cylinder.center, scalar_product(cylinder.normal, calcul));
	normal = vec_subtract(rt->camera.origin, normal);
	dist_cam = vec_magnitude(normal);
	if (dist_cam < cylinder.diameter / 2)
		return (1);
	else
		return (0);
}

double	check_for_m_in_range(t_quadratic *quad, t_cylinder cylinder, t_ray ray)
{
	double	m1;
	double	m2;

	m1 = (dot(ray.direction, cylinder.normal) * quad->t1)
		+ dot(vec_subtract(ray.origin, cylinder.center),
			cylinder.normal);
	m2 = (dot(ray.direction, cylinder.normal) * quad->t2)
		+ dot(vec_subtract(ray.origin, cylinder.center),
			cylinder.normal);
	if (m1 < 0 || m1 > cylinder.height)
		quad->t1 = INFINITY;
	if (m2 < 0 || m2 > cylinder.height)
		quad->t2 = INFINITY;
	return (min_num(quad->t1, quad->t2));
}

void	solve_for_t(t_rt *rt, t_cylinder cylinder, t_ray ray, t_quadratic *quad)
{
	double	result;

	quad->determinant = sqrt(quad->determinant);
	quad->t1 = (-(quad->b) + quad->determinant) / (2 * quad->a);
	quad->t2 = (-(quad->b) - quad->determinant) / (2 * quad->a);
	result = check_for_m_in_range(quad, cylinder, ray);
	if (result < *quad->t)
	{
		*quad->t = result;
		if (!rt->cam_inside)
			calculate_tube_pixel_color(rt, cylinder, ray, quad->t);
		else
			calculate_inside_tube_pixel_color(rt, cylinder, ray, quad->t);
	}
}
