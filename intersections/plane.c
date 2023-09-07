/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshsharma <toshsharma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 16:49:25 by toshsharma        #+#    #+#             */
/*   Updated: 2023/09/07 22:02:34 by toshsharma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

void	intersect_plane(t_rt *rt, t_plane plane, t_ray ray, double *t)
{
	double	denominator;
	double	numerator;
	double	result;

	denominator = dot_product(ray.direction, plane.normal);
	if (denominator == 0)
		return ;
	else
	{
		numerator = dot_product(vec_subtract(plane.center, ray.origin),
				plane.normal);
		result = numerator / denominator;
		if (result < 0)
			return ;
		else if (result < *t && result > 0)
		{
			*t = result;
			// TODO: Do color coding stuff here.
			put_pixel(&rt->img, ray.x, ray.y, 0x0099FF00);
		}
	}
}
