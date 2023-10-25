/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshsharma <toshsharma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 10:38:41 by toshsharma        #+#    #+#             */
/*   Updated: 2023/10/24 23:35:25 by toshsharma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

// int	multiply_light(int pixel_point, int light[3])
// {
// 	int	mask;
// 	int	r;
// 	int	g;
// 	int	b;

// 	mask = 255 << 16;
// 	r = light[0] * ((pixel_point & mask) >> 16);
// 	mask >>= 8;
// 	g = light[1] * ((pixel_point & mask) >> 8);
// 	mask >>= 8;
// 	b = light[2] * (pixel_point & mask);
// 	r = clamp(r, 0, 255);
// 	g = clamp(g, 0, 255);
// 	b = clamp(b, 0, 255);
// 	return ((r << 16) | (g << 8) | b);
// }

// int	multiply_hex_colors(int c1, int c2)
// {
// 	int	color;

// 	color = (int)(((c1 >> 16) % 256 * ((double)(c2 / 65536 % 256)) / 255)) << 16
// 		| (int)(((c1 >> 8) % 256 * ((double)(c2 / 256 % 256)) / 255)) << 8
// 		| (int)(c1 % 256 * ((double)(c2 % 256) / 255));
// 	return (color);
// }

int	add_hex_colors(int c1, int c2)
{
	int	mask;
	int	r;
	int	g;
	int	b;

	mask = 255 << 16;
	r = clamp(((c1 & mask) >> 16) + ((c2 & mask) >> 16), 0, 255);
	mask >>= 8;
	g = clamp(((c1 & mask) >> 8) + ((c2 & mask) >> 8), 0, 255);
	mask >>= 8;
	b = clamp((c1 & mask) + (c2 & mask), 0, 255);
	return (r << 16 | g << 8 | b);
}

int	add_two_colors(int c1[3], double a, int c2[3], double b)
{
	int	result;

	result = clamp((int)(((c1[0] * a) + (c2[0] * b))), 0, 255) << 16
		| clamp((int)(((c1[1] * a) + (c2[1] * b))), 0, 255) << 8
		| clamp((int)(((c1[2] * a) + (c2[2] * b))), 0, 255);
	return (result);
}

int	c_c(t_rt *rt, int input_color[3], double lam_ref, double specular_ref)
{
	int		color;
	double	test;
	double	max;

	max = 255.0 * 255.0 * 255.0;
	test = (double)(input_color[0] * input_color[1] * input_color[2]);
	color = add_hex_colors(array_to_int(input_color, (1.0 - (test / max))
				* lam_ref), array_to_int(rt->ambient->color,
				rt->ambient->brightness));
	color = add_hex_colors(color,
			array_to_int(rt->light->color, lam_ref * rt->light->brightness));
	color = add_hex_colors(color,
			array_to_int(rt->light->color, specular_ref * rt->light->brightness));
	return (color);
}

int	array_to_int(int c[3], double a)
{
	int	result;

	result = (int)(c[0] * a) << 16 | (int)(c[1] * a) << 8 | (int)(c[2] * a);
	return (result);
}
