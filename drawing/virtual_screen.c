/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   virtual_screen.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshsharma <toshsharma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 14:47:34 by toshsharma        #+#    #+#             */
/*   Updated: 2023/10/12 17:27:48 by toshsharma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

// TODO: We need to handle 2 edge cases in setting up the up_guide vector
// one if the camera direction is the up_guide vector
// second, if the camera direction is opposite of the up_guide vector
// TODO: Verify this with Thomas
t_vector	set_up_guide_vector(t_rt *rt)
{
	t_vector	dir;

	dir = vectorize(0, 1, 0);
	if (dot_product(dir, rt->camera.direction) == 0.0)
		return (dir);
	if (dot_product(dir, rt->camera.direction) == 1.0)
		dir = vectorize(0, 0, 1);
	else if (dot_product(dir, rt->camera.direction) == -1.0)
		dir = vectorize(0, 0, -1);
	return (dir);
}

t_vector	set_up_forward_vector(t_rt *rt)
{
	t_vector	dir;

	if (rt->camera.direction.x == 0.0 && rt->camera.direction.y == 0.0
		&& rt->camera.direction.z == 0.0)
		dir = normalize_vector(rt->camera.origin);
	else
		dir = normalize_vector(rt->camera.direction);
	return (dir);
}

void	set_up_vector_directions(t_rt *rt)
{
	rt->img.up_guide = set_up_guide_vector(rt);
	rt->img.forward = set_up_forward_vector(rt);
	rt->img.right = normalize_vector(cross_product(rt->img.forward,
				rt->img.up_guide));
	rt->img.up = cross_product(rt->img.right, rt->img.forward);
	rt->img.img_width = (double) WIDTH;
	rt->img.img_height = (double) HEIGHT;
	if (rt->img.img_width < rt->img.img_height)
	{
		rt->img.img_width = (double) HEIGHT;
		rt->img.img_height = (double) WIDTH;
	}
	rt->img.img_aspect_ratio = rt->img.img_width / rt->img.img_height;
	rt->img.scale = tan(rt->camera.fov * 0.5 * M_PI / 180.0);
}
