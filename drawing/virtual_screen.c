/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   virtual_screen.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshsharma <toshsharma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 14:47:34 by toshsharma        #+#    #+#             */
/*   Updated: 2023/09/03 01:50:56 by toshsharma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

// We need to handle 2 edge cases in setting up the up_guide vector
// one if the camera direction is the up_guide vector
// second, if the camera direction is opposite of the up_guide vector
t_vector	set_up_guide_vector(t_rt *rt)
{
	(void)rt;
	return (return_vector(0, 1, 0));
}

void	set_up_vector_directions(t_rt *rt)
{
	rt->img.up_guide = set_up_guide_vector(rt);
	rt->img.forward = normalize_vector(vec_subtract(rt->camera.direction,
				rt->camera.origin));
	rt->img.right = normalize_vector(cross_product(rt->img.forward,
				rt->img.up_guide));
	rt->img.up = cross_product(rt->img.right, rt->img.forward);
	rt->img.height = tanf(rt->camera.fov * 0.5 * M_PI / 180) * 2;
	rt->img.width = WIDTH / HEIGHT * rt->img.height;
}
